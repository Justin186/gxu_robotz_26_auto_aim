#ifndef TASKS__VIDEO_ENCODER_HPP
#define TASKS__VIDEO_ENCODER_HPP

#include <gst/gst.h>
#include <gst/app/gstappsink.h>
#include <gst/app/gstappsrc.h>
#include <opencv2/opencv.hpp>
#include <thread>
#include <mutex>
#include <atomic>
#include <vector>
#include <deque>
#include <functional>
#include <string>

namespace tasks
{

struct VideoEncoderConfig {
    int crop_size = 800;
    int output_size = 400;
    int output_fps = 60;
    int target_bitrate = 110;          // 画质大幅提升 (约 13.75 kB/s)
    int packet_size = 290;             // 适配 0x0310 协议 (官方上限 300，留出 10 字节包头余量)
    bool static_simplify = true;
    int motion_threshold = 14;
    int motion_erode_px = 1;
    int motion_dilate_px = 2;
    int motion_trail_frames = 3;
    double trail_disable_motion_ratio = 0.30;
    double bg_update_alpha = 0.01;
    double bg_blur_sigma = 1.2;
    int center_clear_size = 100;
    bool force_monochrome = false;
    double bandwidth_limit_kbytes = 14.0;  // 限速提高到 14 kB/s (安全线 below 15 kB/s @ 50包)
    double bandwidth_window_s = 2.0;
    double max_tx_delay_s = 1.0;
    std::string x264_preset = "auto";
};

class VideoEncoder
{
public:
  using PacketCallback = std::function<void(const uint8_t* data, size_t size)>;

  VideoEncoder(const VideoEncoderConfig & config, PacketCallback packet_cb);
  ~VideoEncoder();

  // 推入每一帧画面进行编码
  void push_frame(const cv::Mat & frame, int64_t timestamp_ns = -1);

private:
  void initialize_gstreamer();
  void shutdown_gstreamer();
  
  // 原图处理（去静态、裁剪、缩放等）
  cv::Mat preprocess_image(const cv::Mat & input);
  
  // GStreamer 推拉流
  void push_frame_to_gstreamer(const cv::Mat & frame);
  void pull_stream_and_packetize();

  VideoEncoderConfig config_;
  PacketCallback packet_cb_;

  GstElement * pipeline_ = nullptr;
  GstElement * appsrc_ = nullptr;
  GstElement * appsink_ = nullptr;
  GstBus * bus_ = nullptr;

  std::mutex buffer_mutex_;
  std::vector<uint8_t> stream_buffer_;

  // 带宽限速窗口
  std::deque<std::pair<int64_t, size_t>> sent_window_;
  size_t sent_window_bytes_ = 0;

  // 统计与排队状态
  uint64_t packet_sequence_id_ = 0;
  uint64_t dropped_bytes_ = 0;
  uint32_t dropped_events_ = 0;
  int64_t last_telemetry_ns_ = 0;
  int64_t last_encode_stamp_ns_ = 0;

  // 预处理使用
  cv::Mat background_gray_f32_;
  cv::Mat motion_erode_kernel_;
  cv::Mat motion_dilate_kernel_;
  std::deque<cv::Mat> motion_mask_history_;
  std::deque<cv::Mat> trail_frame_history_;
};

}  // namespace tasks

#endif  // TASKS__VIDEO_ENCODER_HPP