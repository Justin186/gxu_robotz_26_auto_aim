#include "yolov5.hpp"
#include "tasks/auto_aim/trt_infer.hpp"

#include <fmt/chrono.h>
#include <yaml-cpp/yaml.h>

#include <filesystem>
#include <algorithm>
#include <chrono>
#include <cstdint>
#include <cstring>

#include "tools/img_tools.hpp"
#include "tools/logger.hpp"

namespace auto_aim
{
namespace
{
uint16_t fp32_to_fp16_bits(float x)
{
  uint32_t bits;
  std::memcpy(&bits, &x, sizeof(float));
  uint32_t sign = (bits >> 16) & 0x8000u;
  uint32_t mantissa = bits & 0x007fffffu;
  int32_t exp = static_cast<int32_t>((bits >> 23) & 0xffu) - 127 + 15;

  if (exp <= 0) {
    if (exp < -10) {
      return static_cast<uint16_t>(sign);
    }
    mantissa = (mantissa | 0x00800000u) >> (1 - exp);
    return static_cast<uint16_t>(sign | ((mantissa + 0x00001000u) >> 13));
  }
  if (exp >= 31) {
    return static_cast<uint16_t>(sign | 0x7c00u);
  }
  return static_cast<uint16_t>(sign | (static_cast<uint32_t>(exp) << 10) | ((mantissa + 0x00001000u) >> 13));
}
}  // namespace

YOLOV5::YOLOV5(const std::string & config_path, bool debug)
: debug_(debug), detector_(config_path, false)
{
  auto yaml = YAML::LoadFile(config_path);

  model_path_ = yaml["yolov5_model_path"].as<std::string>();
  device_ = yaml["device"].as<std::string>();
  binary_threshold_ = yaml["threshold"].as<double>();
  min_confidence_ = yaml["min_confidence"].as<double>();
  int x = 0, y = 0, width = 0, height = 0;
  x = yaml["roi"]["x"].as<int>();
  y = yaml["roi"]["y"].as<int>();
  width = yaml["roi"]["width"].as<int>();
  height = yaml["roi"]["height"].as<int>();
  use_roi_ = yaml["use_roi"].as<bool>();
  use_traditional_ = yaml["use_traditional"].as<bool>();
  roi_ = cv::Rect(x, y, width, height);
  offset_ = cv::Point2f(x, y);

  save_path_ = "imgs";
  std::filesystem::create_directory(save_path_);
  net_input_ = cv::Mat(640, 640, CV_8UC3, cv::Scalar(0, 0, 0));
  trt_input_buffer_.resize(3 * 640 * 640);
  trt_output_buffer_.resize(25200 * 22);
  parse_color_ids_.reserve(25200);
  parse_num_ids_.reserve(25200);
  parse_confidences_.reserve(25200);
  parse_boxes_.reserve(25200);
  parse_keypoints_.reserve(25200);

  auto ext = std::filesystem::path(model_path_).extension().string();
  std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
  if (ext == ".engine" || ext == ".trt") {
    use_trt_ = true;
    trt_infer_ = std::make_unique<TRTInfer>(model_path_);
  } else {
    use_trt_ = false;
    yolo_net_ = cv::dnn::readNet(model_path_);
  }
  /*
  ov::preprocess::PrePostProcessor ppp(model);
  auto & input = ppp.input();

  input.tensor()
    .set_element_type(ov::element::u8)
    .set_shape({1, 640, 640, 3})
    .set_layout("NHWC")
    .set_color_format(ov::preprocess::ColorFormat::BGR);

  input.model().set_layout("NCHW");

  input.preprocess()
    .convert_element_type(ov::element::f32)
    .convert_color(ov::preprocess::ColorFormat::RGB)
    .scale(255.0);

  // TODO: ov::hint::performance_mode(ov::hint::PerformanceMode::LATENCY)
  model = ppp.build();
  compiled_model_ = core_.compile_model(
    model, device_, ov::hint::performance_mode(ov::hint::PerformanceMode::LATENCY));
  */
}

std::list<Armor> YOLOV5::detect(const cv::Mat & raw_img, int frame_count)
{
  return detect_impl(raw_img, frame_count, nullptr);
}

std::list<Armor> YOLOV5::detect(const cv::Mat & raw_img, int frame_count, cv::Mat & out_debug_img)
{
  return detect_impl(raw_img, frame_count, &out_debug_img);
}

std::list<Armor> YOLOV5::detect_impl(const cv::Mat & raw_img, int frame_count, cv::Mat * out_debug_img)
{
  const auto t_total_begin = std::chrono::steady_clock::now();
  if (raw_img.empty()) {
    tools::logger()->warn("Empty img!, camera drop!");
    return std::list<Armor>();
  }

  cv::Mat bgr_img;
  if (use_roi_) {
    if (roi_.width == -1) {  // -1 表示该维度不裁切
      roi_.width = raw_img.cols;
    }
    if (roi_.height == -1) {  // -1 表示该维度不裁切
      roi_.height = raw_img.rows;
    }
    bgr_img = raw_img(roi_);
  } else {
    bgr_img = raw_img;
  }

  auto x_scale = static_cast<double>(640) / bgr_img.rows;
  auto y_scale = static_cast<double>(640) / bgr_img.cols;
  auto scale = std::min(x_scale, y_scale);
  auto h = static_cast<int>(bgr_img.rows * scale);
  auto w = static_cast<int>(bgr_img.cols * scale);

  // preproces
  const auto t_pre_begin = std::chrono::steady_clock::now();
  net_input_.setTo(cv::Scalar(0, 0, 0));
  auto roi = cv::Rect(0, 0, w, h);
  cv::resize(bgr_img, net_input_(roi), {w, h});
  if (use_trt_) {
    constexpr int input_h = 640;
    constexpr int input_w = 640;
    constexpr float inv_255 = 1.0f / 255.0f;
    const int channel_stride = input_h * input_w;
    uint16_t * r = trt_input_buffer_.data();
    uint16_t * g = r + channel_stride;
    uint16_t * b = g + channel_stride;

    for (int y = 0; y < input_h; ++y) {
      const cv::Vec3b * row_ptr = net_input_.ptr<cv::Vec3b>(y);
      int base = y * input_w;
      for (int x = 0; x < input_w; ++x) {
        const cv::Vec3b & px = row_ptr[x];
        const int idx = base + x;
        r[idx] = fp32_to_fp16_bits(static_cast<float>(px[2]) * inv_255);
        g[idx] = fp32_to_fp16_bits(static_cast<float>(px[1]) * inv_255);
        b[idx] = fp32_to_fp16_bits(static_cast<float>(px[0]) * inv_255);
      }
    }
  } else {
    cv::dnn::blobFromImage(net_input_, blob_, 1.0 / 255.0, cv::Size(), cv::Scalar(), true, false, CV_32F);
  }
  const auto t_pre_end = std::chrono::steady_clock::now();

  const auto t_infer_begin = std::chrono::steady_clock::now();
  cv::Mat output;
  if (use_trt_) {
    int output_elements = 25200 * 22;
    trt_infer_->infer(trt_input_buffer_.data(), trt_output_buffer_.data(), 640, 640, 3, output_elements);
    output = cv::Mat(25200, 22, CV_32F, trt_output_buffer_.data());
    if (output.rows == 22 && output.cols == 25200) {
      output = output.t();
    }
  } else {
    yolo_net_.setInput(blob_);
    cv::Mat raw = yolo_net_.forward();
    if (raw.dims == 3 && raw.size[0] == 1) {
      output = cv::Mat(raw.size[1], raw.size[2], CV_32F, raw.ptr<float>()).clone();
    } else if (raw.dims == 4 && raw.size[0] == 1 && raw.size[1] == 1) {
      output = cv::Mat(raw.size[2], raw.size[3], CV_32F, raw.ptr<float>()).clone();
    } else if (raw.dims == 2) {
      output = raw;
    } else {
      throw std::runtime_error("Unsupported YOLOv5 output shape from OpenCV DNN");
    }
    if (output.rows == 22 && output.cols == 25200) {
      output = output.t();
    }
  }
  const auto t_infer_end = std::chrono::steady_clock::now();

  const auto t_post_begin = std::chrono::steady_clock::now();
  auto armors = parse(scale, output, raw_img, frame_count, out_debug_img);
  const auto t_post_end = std::chrono::steady_clock::now();

  if (frame_count >= 0 && frame_count % 30 == 0) {
    const double pre_ms = std::chrono::duration<double, std::milli>(t_pre_end - t_pre_begin).count();
    const double infer_ms = std::chrono::duration<double, std::milli>(t_infer_end - t_infer_begin).count();
    const double post_ms = std::chrono::duration<double, std::milli>(t_post_end - t_post_begin).count();
    const double total_ms = std::chrono::duration<double, std::milli>(t_post_end - t_total_begin).count();
    tools::logger()->info(
      "[YOLOv5 profile] frame={} pre={:.2f}ms infer={:.2f}ms post={:.2f}ms total={:.2f}ms",
      frame_count, pre_ms, infer_ms, post_ms, total_ms);
  }

  return armors;
}

std::list<Armor> YOLOV5::parse(
  double scale, cv::Mat & output, const cv::Mat & bgr_img, int frame_count, cv::Mat * out_debug_img)
{
  // for each row: xywh + classess
  parse_color_ids_.clear();
  parse_num_ids_.clear();
  parse_confidences_.clear();
  parse_boxes_.clear();
  parse_keypoints_.clear();

  for (int r = 0; r < output.rows; r++) {
    const float * row = output.ptr<float>(r);
    double score = row[8];
    score = sigmoid(score);

    if (score < score_threshold_) continue;

    int _color_id = 0;
    int _class_id = 0;
    float color_max = row[9];
    for (int i = 1; i < 4; ++i) {
      if (row[9 + i] > color_max) {
        color_max = row[9 + i];
        _color_id = i;
      }
    }
    float class_max = row[13];
    for (int i = 1; i < 9; ++i) {
      if (row[13 + i] > class_max) {
        class_max = row[13 + i];
        _class_id = i;
      }
    }

    std::array<cv::Point2f, 4> keypoints{
      cv::Point2f(row[0] / scale, row[1] / scale),
      cv::Point2f(row[6] / scale, row[7] / scale),
      cv::Point2f(row[4] / scale, row[5] / scale),
      cv::Point2f(row[2] / scale, row[3] / scale)};

    float min_x = keypoints[0].x;
    float max_x = keypoints[0].x;
    float min_y = keypoints[0].y;
    float max_y = keypoints[0].y;

    for (size_t i = 1; i < keypoints.size(); i++) {
      if (keypoints[i].x < min_x) min_x = keypoints[i].x;
      if (keypoints[i].x > max_x) max_x = keypoints[i].x;
      if (keypoints[i].y < min_y) min_y = keypoints[i].y;
      if (keypoints[i].y > max_y) max_y = keypoints[i].y;
    }

    cv::Rect rect(min_x, min_y, max_x - min_x, max_y - min_y);

    parse_color_ids_.emplace_back(_color_id);
    parse_num_ids_.emplace_back(_class_id);
    parse_boxes_.emplace_back(rect);
    parse_confidences_.emplace_back(score);
    parse_keypoints_.emplace_back(keypoints);
  }

  std::vector<int> indices;
  cv::dnn::NMSBoxes(parse_boxes_, parse_confidences_, score_threshold_, nms_threshold_, indices);

  std::list<Armor> armors;
  for (const auto & i : indices) {
    std::vector<cv::Point2f> armor_key_points{
      parse_keypoints_[i][0], parse_keypoints_[i][1], parse_keypoints_[i][2], parse_keypoints_[i][3]};
    if (use_roi_) {
      armors.emplace_back(
        parse_color_ids_[i], parse_num_ids_[i], parse_confidences_[i], parse_boxes_[i],
        std::move(armor_key_points), offset_);
    } else {
      armors.emplace_back(
        parse_color_ids_[i], parse_num_ids_[i], parse_confidences_[i], parse_boxes_[i],
        std::move(armor_key_points));
    }
  }

  tmp_img_ = bgr_img;
  for (auto it = armors.begin(); it != armors.end();) {
    if (!check_name(*it)) {
      it = armors.erase(it);
      continue;
    }

    if (!check_type(*it)) {
      it = armors.erase(it);
      continue;
    }
    // 使用传统方法二次矫正角点
    if (use_traditional_) detector_.detect(*it, bgr_img);

    it->center_norm = get_center_norm(bgr_img, it->center);
    ++it;
  }

  if (debug_) draw_detections(bgr_img, armors, frame_count, out_debug_img);

  return armors;
}

bool YOLOV5::check_name(const Armor & armor) const
{
  auto name_ok = armor.name != ArmorName::not_armor;
  auto confidence_ok = armor.confidence > min_confidence_;

  // 保存不确定的图案，用于神经网络的迭代
  // if (name_ok && !confidence_ok) save(armor);

  return name_ok && confidence_ok;
}

bool YOLOV5::check_type(const Armor & armor) const
{
  auto name_ok = (armor.type == ArmorType::small)
                   ? (armor.name != ArmorName::one && armor.name != ArmorName::base)
                   : (armor.name != ArmorName::two && armor.name != ArmorName::sentry &&
                      armor.name != ArmorName::outpost);

  // 保存异常的图案，用于神经网络的迭代
  // if (!name_ok) save(armor);

  return name_ok;
}

cv::Point2f YOLOV5::get_center_norm(const cv::Mat & bgr_img, const cv::Point2f & center) const
{
  auto h = bgr_img.rows;
  auto w = bgr_img.cols;
  return {center.x / w, center.y / h};
}

void YOLOV5::draw_detections(
  const cv::Mat & img, const std::list<Armor> & armors, int frame_count, cv::Mat * out_debug_img) const
{
  auto detection = img.clone();
  tools::draw_text(detection, fmt::format("[{}]", frame_count), {10, 30}, {255, 0, 0});
  for (const auto & armor : armors) {
    auto info = fmt::format(
      "{:.2f} {} {} {}", armor.confidence, COLORS[armor.color], ARMOR_NAMES[armor.name],
      ARMOR_TYPES[armor.type]);
    tools::draw_points(detection, armor.points, {0, 255, 0});
    tools::draw_text(detection, info, armor.center, {0, 255, 0});
  }

  if (use_roi_) {
    cv::Scalar green(0, 255, 0);
    cv::rectangle(detection, roi_, green, 2);
  }
  
  if (out_debug_img) {
    *out_debug_img = detection.clone();
  } else {
    cv::resize(detection, detection, {}, 0.5, 0.5);  // 显示时缩小图片尺寸
    cv::imshow("detection", detection);
  }
}

void YOLOV5::save(const Armor & armor) const
{
  auto file_name = fmt::format("{:%Y-%m-%d_%H-%M-%S}", std::chrono::system_clock::now());
  auto img_path = fmt::format("{}/{}_{}.jpg", save_path_, armor.name, file_name);
  cv::imwrite(img_path, tmp_img_);
}

double YOLOV5::sigmoid(double x)
{
  if (x > 0)
    return 1.0 / (1.0 + exp(-x));
  else
    return exp(x) / (1.0 + exp(x));
}

std::list<Armor> YOLOV5::postprocess(
  double scale, cv::Mat & output, const cv::Mat & bgr_img, int frame_count)
{
  return parse(scale, output, bgr_img, frame_count);
}

}  // namespace auto_aim