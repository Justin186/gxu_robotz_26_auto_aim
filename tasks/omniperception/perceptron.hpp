#ifndef OMNIPERCEPTION__PERCEPTRON_HPP
#define OMNIPERCEPTION__PERCEPTRON_HPP

#include <chrono>
#include <atomic>
#include <functional>
#include <mutex>
#include <memory>
#include <string>
#include <thread>
#include <opencv2/core/mat.hpp>

#include "tasks/omniperception/detection.hpp"

namespace io
{
class USBCamera;
}

namespace auto_aim
{
class YOLO;
}

namespace omniperception
{
//无图，无目标，有目标
enum class DetectStatus
{
  no_frame,
  no_target,
  detected
};

class Perceptron
{
public:
  // 左侧相机复用 GimbalNode 暴露出来的 ROS 图像读取接口
  using LeftImageReader =
    std::function<bool(cv::Mat &, std::chrono::steady_clock::time_point &)>;
  using LeftImageClearer = std::function<void()>;

  Perceptron(
    LeftImageReader left_reader, LeftImageClearer left_clearer, io::USBCamera * right_cam,
    const std::string & config_path);
  ~Perceptron();

  void clear_side_buffers();
  bool get_latest_left_image(cv::Mat & img);
  bool get_latest_right_image(cv::Mat & img);
  bool get_latest_left_armors(std::list<auto_aim::Armor> & armors);
  bool get_latest_right_armors(std::list<auto_aim::Armor> & armors);
  // Perceptron 只做侧向检测，过滤和决策统一留给 Decider
  // no_frame: 这轮没有拿到新图
  // no_target: 拿到了新图，但图里没有目标
  // detected: 拿到了新图，并且有检测结果
  DetectStatus detect_left(DetectionResult & result);
  DetectStatus detect_right(DetectionResult & result);

private:
  struct CachedDetection
  {
    DetectStatus status = DetectStatus::no_frame;
    DetectionResult result;
    bool has_update = false;
  };

  bool detect_left_once();
  bool detect_right_once();
  void detection_loop();
  DetectStatus take_cached_detection(bool left, DetectionResult & result);

  LeftImageReader left_reader_;
  LeftImageClearer left_clearer_;
  io::USBCamera * right_cam_;
  std::mutex debug_image_mutex_;
  std::mutex detection_mutex_;
  cv::Mat latest_left_img_;
  cv::Mat latest_right_img_;
  std::list<auto_aim::Armor> latest_left_armors_;
  std::list<auto_aim::Armor> latest_right_armors_;
  CachedDetection left_detection_;
  CachedDetection right_detection_;
  std::atomic<bool> quit_{false};
  std::thread detection_thread_;

  // 左右侧共用一个 YOLO，避免额外复制模型和占用过多 CPU
  std::shared_ptr<auto_aim::YOLO> yolo_side_;
};

}  // namespace omniperception

#endif
