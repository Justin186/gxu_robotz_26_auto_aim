#ifndef OMNIPERCEPTION__PERCEPTRON_HPP
#define OMNIPERCEPTION__PERCEPTRON_HPP

#include <chrono>
#include <functional>
#include <memory>
#include <string>
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

  void clear_side_buffers();
  // Perceptron 只做侧向检测，过滤和决策统一留给 Decider
  // no_frame: 这轮没有拿到新图
  // no_target: 拿到了新图，但图里没有目标
  // detected: 拿到了新图，并且有检测结果
  DetectStatus detect_left(DetectionResult & result);
  DetectStatus detect_right(DetectionResult & result);

private:
  LeftImageReader left_reader_;
  LeftImageClearer left_clearer_;
  io::USBCamera * right_cam_;

  // 左右侧共用一个 YOLO，避免额外复制模型和占用过多 CPU
  std::shared_ptr<auto_aim::YOLO> yolo_side_;
};

}  // namespace omniperception

#endif
