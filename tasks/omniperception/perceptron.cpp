#include "perceptron.hpp"

#include "io/usbcamera/usbcamera.hpp"
#include "tasks/auto_aim/yolo.hpp"

namespace omniperception
{
Perceptron::Perceptron(
  LeftImageReader left_reader, LeftImageClearer left_clearer, io::USBCamera * right_cam,
  const std::string & config_path)
: left_reader_(std::move(left_reader)), left_clearer_(std::move(left_clearer)), right_cam_(right_cam)
{
  yolo_side_ = std::make_shared<auto_aim::YOLO>(config_path, false);
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
}

DetectStatus Perceptron::detect_left(DetectionResult & result)
{
  cv::Mat img;
  std::chrono::steady_clock::time_point ts;
  if (!left_reader_ || !left_reader_(img, ts) || img.empty()) return DetectStatus::no_frame;

  // 这里只返回原始检测结果，后续过滤、排序、角度换算都在 Decider 里做
  auto armors = yolo_side_->detect(img);
  if (armors.empty()) return DetectStatus::no_target;
  result.armors = std::move(armors);
  result.timestamp = ts;
  result.source = "left";
  result.delta_yaw = 0.0;
  result.delta_pitch = 0.0;
  return DetectStatus::detected;
}

DetectStatus Perceptron::detect_right(DetectionResult & result)
{
  if (!right_cam_) return DetectStatus::no_frame;

  cv::Mat img;
  std::chrono::steady_clock::time_point ts;
  // 右侧 USB 相机用非阻塞读，避免控制线程被低帧率相机卡住
  if (!right_cam_->try_read(img, ts) || img.empty()) return DetectStatus::no_frame;

  auto armors = yolo_side_->detect(img);
  if (armors.empty()) return DetectStatus::no_target;
  result.armors = std::move(armors);
  result.timestamp = ts;
  result.source = "right";
  result.delta_yaw = 0.0;
  result.delta_pitch = 0.0;
  return DetectStatus::detected;
}

}  // namespace omniperception
