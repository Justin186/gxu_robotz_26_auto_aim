#include "tasks/video_encoder/video_encoder.hpp"
#include <chrono>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <iostream>

namespace tasks
{

VideoEncoder::VideoEncoder(const VideoEncoderConfig & config, PacketCallback packet_cb)
: config_(config),
  packet_cb_(std::move(packet_cb)),
  pipeline_(nullptr),
  appsrc_(nullptr),
  appsink_(nullptr),
  bus_(nullptr),
  packet_sequence_id_(0),
  dropped_bytes_(0),
  dropped_events_(0)
{
  initialize_gstreamer();
}

VideoEncoder::~VideoEncoder()
{
  shutdown_gstreamer();
}

void VideoEncoder::initialize_gstreamer()
{
  gst_init(nullptr, nullptr);

  pipeline_ = gst_pipeline_new("encoder_pipe");
  appsrc_ = gst_element_factory_make("appsrc", "source");
  appsink_ = gst_element_factory_make("appsink", "sink");
  GstElement *convert = gst_element_factory_make("videoconvert", "convert");
  GstElement *encoder = gst_element_factory_make("x264enc", "encoder");
  GstElement *parser = gst_element_factory_make("h264parse", "parser");

  if (!pipeline_ || !appsrc_ || !appsink_ || !convert || !encoder || !parser) {
    std::cerr << "[VideoEncoder] GStreamer element creation failed" << std::endl;
    return;
  }

  GstCaps *caps = gst_caps_new_simple(
    "video/x-raw",
    "format", G_TYPE_STRING, "BGR",
    "width", G_TYPE_INT, config_.output_size,
    "height", G_TYPE_INT, config_.output_size,
    "framerate", GST_TYPE_FRACTION, config_.output_fps, 1,
    nullptr);
  g_object_set(G_OBJECT(appsrc_),
    "caps", caps,
    "stream-type", 0,
    "format", GST_FORMAT_TIME,
    "is-live", TRUE,
    "do-timestamp", TRUE,
    nullptr);
  gst_caps_unref(caps);

  const bool low_bitrate_mode = (config_.target_bitrate <= 80);
  const int key_int = std::max(8 * config_.output_fps, 30);
  const int default_speed_preset = low_bitrate_mode ? 9 : 3;
  int speed_preset = default_speed_preset;
  // TODO: Add full preset parsing (omitted here for brevity, matching simple setup)
  if (config_.x264_preset == "veryslow") speed_preset = 9;

  if (low_bitrate_mode) {
    g_object_set(
      G_OBJECT(encoder),
      "bitrate", config_.target_bitrate,
      "speed-preset", speed_preset,
      "tune", 0,
      "byte-stream", TRUE,
      "key-int-max", key_int,
      "bframes", 4,
      "rc-lookahead", 40,
      "sync-lookahead", 20,
      "sliced-threads", FALSE,
      "ref", 5,
      "aud", TRUE,
      "vbv-buf-capacity", 500,
      "option-string", "repeat-headers=1:scenecut=0:aq-mode=2:aq-strength=1.2:mbtree=1:qcomp=0.75:subme=8:trellis=2:deblock=1,1:force-cfr=1",
      "pass", 0,
      nullptr);
  } else {
    g_object_set(
      G_OBJECT(encoder),
      "bitrate", config_.target_bitrate,
      "speed-preset", speed_preset,
      "tune", 0x00000004,
      "byte-stream", TRUE,
      "key-int-max", 2 * config_.output_fps,
      "bframes", 0,
      "rc-lookahead", 0,
      "sync-lookahead", 0,
      "sliced-threads", TRUE,
      "aud", TRUE,
      "option-string", "repeat-headers=1:scenecut=0:ref=1:force-cfr=1",
      "pass", 0,
      nullptr);
  }

  g_object_set(
    G_OBJECT(parser),
    "config-interval", -1,
    "disable-passthrough", TRUE,
    nullptr);

  GstCaps *h264_caps = gst_caps_new_simple(
    "video/x-h264",
    "stream-format", G_TYPE_STRING, "byte-stream",
    "alignment", G_TYPE_STRING, "au",
    nullptr);

  g_object_set(G_OBJECT(appsink_),
    "caps", h264_caps,
    "max-buffers", 5,
    "drop", FALSE,
    "emit-signals", FALSE,
    "sync", FALSE,
    nullptr);
  gst_caps_unref(h264_caps);

  gst_bin_add_many(GST_BIN(pipeline_), appsrc_, convert, encoder, parser, appsink_, nullptr);
  if (!gst_element_link_many(appsrc_, convert, encoder, parser, appsink_, nullptr)) {
    std::cerr << "[VideoEncoder] GStreamer pipeline link failed" << std::endl;
    return;
  }

  if (gst_element_set_state(pipeline_, GST_STATE_PLAYING) == GST_STATE_CHANGE_FAILURE) {
    std::cerr << "[VideoEncoder] GStreamer pipeline start failed" << std::endl;
    return;
  }
}

void VideoEncoder::shutdown_gstreamer()
{
  if (pipeline_) {
    gst_element_set_state(pipeline_, GST_STATE_NULL);
    if (bus_) gst_object_unref(bus_);
    gst_object_unref(pipeline_);
    pipeline_ = nullptr;
  }
}

cv::Mat VideoEncoder::preprocess_image(const cv::Mat & input)
{
  int x = (input.cols - config_.crop_size) / 2;
  int y = (input.rows - config_.crop_size) / 2;
  x = std::max(0, x);
  y = std::max(0, y);
  int w = std::min(config_.crop_size, input.cols - x);
  int h = std::min(config_.crop_size, input.rows - y);

  cv::Mat cropped = input(cv::Rect(x, y, w, h));
  cv::Mat resized;
  cv::resize(cropped, resized, cv::Size(config_.output_size, config_.output_size), 0, 0, cv::INTER_LINEAR);
  
  if (config_.force_monochrome) {
    cv::Mat gray;
    cv::cvtColor(resized, gray, cv::COLOR_BGR2GRAY);
    cv::cvtColor(gray, resized, cv::COLOR_GRAY2BGR);
  }

  if (!config_.static_simplify) {
    return resized;
  }

  cv::Mat gray;
  cv::cvtColor(resized, gray, cv::COLOR_BGR2GRAY);
  if (background_gray_f32_.empty()) {
    gray.convertTo(background_gray_f32_, CV_32F);
    return resized;
  }

  cv::Mat bg_u8;
  cv::convertScaleAbs(background_gray_f32_, bg_u8);
  cv::Mat diff, motion_mask;
  cv::absdiff(gray, bg_u8, diff);
  cv::threshold(diff, motion_mask, config_.motion_threshold, 255, cv::THRESH_BINARY);

  if (config_.motion_erode_px > 0) {
    if (motion_erode_kernel_.empty()) {
      const int k = 2 * config_.motion_erode_px + 1;
      motion_erode_kernel_ = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(k, k));
    }
    cv::erode(motion_mask, motion_mask, motion_erode_kernel_);
  }
  if (config_.motion_dilate_px > 0) {
    if (motion_dilate_kernel_.empty()) {
      const int k = 2 * config_.motion_dilate_px + 1;
      motion_dilate_kernel_ = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(k, k));
    }
    cv::dilate(motion_mask, motion_mask, motion_dilate_kernel_);
  }

  const double motion_ratio_raw = 
    static_cast<double>(cv::countNonZero(motion_mask)) / static_cast<double>(motion_mask.total());
  const bool suppress_trail = (motion_ratio_raw >= config_.trail_disable_motion_ratio);

  if (config_.center_clear_size > 0) {
    int clear = std::min({config_.center_clear_size, resized.cols, resized.rows});
    cv::rectangle(motion_mask, 
                  cv::Rect(std::max(0, resized.cols/2 - clear/2), std::max(0, resized.rows/2 - clear/2), 
                           std::min(clear, resized.cols - std::max(0, resized.cols/2 - clear/2)), 
                           std::min(clear, resized.rows - std::max(0, resized.rows/2 - clear/2))), 
                  cv::Scalar(255), cv::FILLED);
  }

  cv::Mat static_base = resized.clone();
  if (!config_.force_monochrome && config_.target_bitrate <= 80) {
    cv::Mat gray_bg;
    cv::cvtColor(static_base, gray_bg, cv::COLOR_BGR2GRAY);
    cv::cvtColor(gray_bg, static_base, cv::COLOR_GRAY2BGR);
  }

  cv::Mat blurred;
  cv::GaussianBlur(static_base, blurred, cv::Size(), config_.bg_blur_sigma, config_.bg_blur_sigma);

  cv::Mat focused = blurred.clone();
  resized.copyTo(focused, motion_mask);

  // 运动拖影：简单时域 max（当前+历史N帧），仅作用在运动区域联合掩码
  if (config_.motion_trail_frames > 0) {
    motion_mask_history_.push_back(motion_mask.clone());
    trail_frame_history_.push_back(resized.clone());
    const size_t max_history = static_cast<size_t>(config_.motion_trail_frames + 1);
    while (motion_mask_history_.size() > max_history) {
      motion_mask_history_.pop_front();
    }
    while (trail_frame_history_.size() > max_history) {
      trail_frame_history_.pop_front();
    }

    const size_t history_size = motion_mask_history_.size();
    if (!suppress_trail && history_size > 1 && history_size == trail_frame_history_.size()) {
      cv::Mat trail_mask = motion_mask.clone();
      cv::Mat trail_img = resized.clone();
      for (size_t i = 0; i < history_size - 1; ++i) {
        cv::bitwise_or(trail_mask, motion_mask_history_[i], trail_mask);
        cv::max(trail_img, trail_frame_history_[i], trail_img);
      }
      trail_img.copyTo(focused, trail_mask);
    }
  } else {
    motion_mask_history_.clear();
    trail_frame_history_.clear();
  }

  cv::accumulateWeighted(gray, background_gray_f32_, config_.bg_update_alpha);
  return focused;
}

void VideoEncoder::push_frame(const cv::Mat & frame, int64_t timestamp_ns)
{
  auto now_ns = std::chrono::system_clock::now().time_since_epoch().count();
  if (timestamp_ns < 0) timestamp_ns = now_ns;

  if (config_.output_fps < 60) {
    int64_t frame_interval = 1000000000LL / std::max(config_.output_fps, 1);
    if (last_encode_stamp_ns_ > 0 && (now_ns - last_encode_stamp_ns_) < frame_interval) {
      return;
    }
    last_encode_stamp_ns_ = now_ns;
  }

  cv::Mat processed = preprocess_image(frame);
  push_frame_to_gstreamer(processed);
  pull_stream_and_packetize();
}

void VideoEncoder::push_frame_to_gstreamer(const cv::Mat & frame)
{
  if (!appsrc_ || frame.empty()) return;
  size_t size = frame.total() * frame.elemSize();
  GstBuffer *buffer = gst_buffer_new_allocate(nullptr, size, nullptr);
  GstMapInfo map;
  if (gst_buffer_map(buffer, &map, GST_MAP_WRITE)) {
    memcpy(map.data, frame.data, size);
    gst_buffer_unmap(buffer, &map);
    GstFlowReturn ret;
    g_signal_emit_by_name(appsrc_, "push-buffer", buffer, &ret);
  }
  gst_buffer_unref(buffer);
}

void VideoEncoder::pull_stream_and_packetize()
{
  if (!appsink_) return;

  uint64_t now_ns = std::chrono::system_clock::now().time_since_epoch().count();
  size_t packet_bytes = config_.packet_size;
  int64_t window_ns = config_.bandwidth_window_s * 1e9;
  size_t window_limit = config_.bandwidth_limit_kbytes * 1000.0 * config_.bandwidth_window_s;

  while (true) {
    GstSample *sample = gst_app_sink_try_pull_sample(GST_APP_SINK(appsink_), 0);
    if (!sample) break;

    GstBuffer *buffer = gst_sample_get_buffer(sample);
    if (!buffer) { gst_sample_unref(sample); continue; }

    GstMapInfo map;
    if (gst_buffer_map(buffer, &map, GST_MAP_READ)) {
      std::lock_guard<std::mutex> lock(buffer_mutex_);
      size_t old_size = stream_buffer_.size();
      stream_buffer_.resize(old_size + map.size);
      memcpy(stream_buffer_.data() + old_size, map.data, map.size);

      while (stream_buffer_.size() >= packet_bytes) {
        while (!sent_window_.empty() && (now_ns - sent_window_.front().first) > window_ns) {
          sent_window_bytes_ -= sent_window_.front().second;
          sent_window_.pop_front();
        }
        if (sent_window_bytes_ + packet_bytes > window_limit) break;

        // 调用刚才传入的回调（直接传进串口或任意其他形式）
        if (packet_cb_) {
            packet_cb_(stream_buffer_.data(), packet_bytes);
        }

        sent_window_.emplace_back(now_ns, packet_bytes);
        sent_window_bytes_ += packet_bytes;
        memmove(stream_buffer_.data(), stream_buffer_.data() + packet_bytes, stream_buffer_.size() - packet_bytes);
        stream_buffer_.resize(stream_buffer_.size() - packet_bytes);
      }
      gst_buffer_unmap(buffer, &map);
    }
    gst_sample_unref(sample);
  }
}

}  // namespace tasks