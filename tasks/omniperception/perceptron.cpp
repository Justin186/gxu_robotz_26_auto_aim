#include "perceptron.hpp"

#include "io/usbcamera/usbcamera.hpp"
#include "tasks/auto_aim/yolo.hpp"

using namespace std::chrono_literals;

namespace omniperception
{
Perceptron::Perceptron(
  LeftImageReader left_reader, LeftImageClearer left_clearer, io::USBCamera * right_cam,
  const std::string & config_path)
: left_reader_(std::move(left_reader)), left_clearer_(std::move(left_clearer)), right_cam_(right_cam)
{
  yolo_side_ = std::make_shared<auto_aim::YOLO>(config_path, false);
  detection_thread_ = std::thread(&Perceptron::detection_loop, this);
}

Perceptron::~Perceptron()
{
  quit_ = true;
  if (detection_thread_.joinable()) {
    detection_thread_.join();
  }
}

void Perceptron::clear_side_buffers()
{
  // 主相机重新接管时，把侧向残留旧帧清掉，避免后面误用旧目标
  if (left_clearer_) {
    left_clearer_();
  }
  if (right_cam_) {
    right_cam_->clear_buffer();
  }
  std::lock_guard<std::mutex> lock(debug_image_mutex_);
  latest_left_img_.release();
  latest_right_img_.release();
  latest_left_armors_.clear();
  latest_right_armors_.clear();

  std::lock_guard<std::mutex> detection_lock(detection_mutex_);
  left_detection_ = {};
  right_detection_ = {};
}

bool Perceptron::get_latest_left_image(cv::Mat & img)
{
  std::lock_guard<std::mutex> lock(debug_image_mutex_);
  if (latest_left_img_.empty()) {
    return false;
  }
  img = latest_left_img_.clone();
  return true;
}

bool Perceptron::get_latest_right_image(cv::Mat & img)
{
  std::lock_guard<std::mutex> lock(debug_image_mutex_);
  if (latest_right_img_.empty()) {
    return false;
  }
  img = latest_right_img_.clone();
  return true;
}

bool Perceptron::get_latest_left_armors(std::list<auto_aim::Armor> & armors)
{
  std::lock_guard<std::mutex> lock(debug_image_mutex_);
  armors = latest_left_armors_;
  return !armors.empty();
}

bool Perceptron::get_latest_right_armors(std::list<auto_aim::Armor> & armors)
{
  std::lock_guard<std::mutex> lock(debug_image_mutex_);
  armors = latest_right_armors_;
  return !armors.empty();
}

DetectStatus Perceptron::detect_left(DetectionResult & result)
{
  return take_cached_detection(true, result);
}

DetectStatus Perceptron::detect_right(DetectionResult & result)
{
  return take_cached_detection(false, result);
}

DetectStatus Perceptron::take_cached_detection(bool left, DetectionResult & result)
{
  std::lock_guard<std::mutex> lock(detection_mutex_);
  auto & cached = left ? left_detection_ : right_detection_;
  if (!cached.has_update) {
    return DetectStatus::no_frame;
  }

  cached.has_update = false;
  if (cached.status == DetectStatus::detected) {
    result = cached.result;
  }
  return cached.status;
}

bool Perceptron::detect_left_once()
{
  cv::Mat img;
  std::chrono::steady_clock::time_point ts;
  if (!left_reader_ || !left_reader_(img, ts) || img.empty()) return false;

  {
    std::lock_guard<std::mutex> lock(debug_image_mutex_);
    latest_left_img_ = img.clone();
  }

  // 这里只返回原始检测结果，后续过滤、排序、角度换算都在 Decider 里做
  auto armors = yolo_side_->detect(img);
  {
    std::lock_guard<std::mutex> lock(debug_image_mutex_);
    latest_left_armors_ = armors;
  }

  DetectionResult result;
  result.armors = std::move(armors);
  result.timestamp = ts;
  result.source = "left";
  result.delta_yaw = 0.0;
  result.delta_pitch = 0.0;

  std::lock_guard<std::mutex> lock(detection_mutex_);
  left_detection_.status =
    result.armors.empty() ? DetectStatus::no_target : DetectStatus::detected;
  left_detection_.result = std::move(result);
  left_detection_.has_update = true;
  return true;
}

bool Perceptron::detect_right_once()
{
  if (!right_cam_) return false;

  cv::Mat img;
  std::chrono::steady_clock::time_point ts;
  if (!right_cam_->try_read(img, ts) || img.empty()) return false;

  {
    std::lock_guard<std::mutex> lock(debug_image_mutex_);
    latest_right_img_ = img.clone();
  }

  auto armors = yolo_side_->detect(img);
  {
    std::lock_guard<std::mutex> lock(debug_image_mutex_);
    latest_right_armors_ = armors;
  }

  DetectionResult result;
  result.armors = std::move(armors);
  result.timestamp = ts;
  result.source = "right";
  result.delta_yaw = 0.0;
  result.delta_pitch = 0.0;

  std::lock_guard<std::mutex> lock(detection_mutex_);
  right_detection_.status =
    result.armors.empty() ? DetectStatus::no_target : DetectStatus::detected;
  right_detection_.result = std::move(result);
  right_detection_.has_update = true;
  return true;
}

void Perceptron::detection_loop()
{
  bool detect_left_next = true;
  while (!quit_) {
    const bool got_frame = detect_left_next ? detect_left_once() : detect_right_once();
    detect_left_next = !detect_left_next;

    if (!got_frame) {
      std::this_thread::sleep_for(1ms);
    }
  }
}

}  // namespace omniperception
