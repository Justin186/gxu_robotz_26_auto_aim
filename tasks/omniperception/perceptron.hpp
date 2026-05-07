#ifndef OMNIPERCEPTION__PERCEPTRON_HPP
#define OMNIPERCEPTION__PERCEPTRON_HPP

#include <chrono>
#include <functional>
#include <list>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include <Eigen/Dense>
#include <opencv2/core/mat.hpp>

#include "tasks/auto_aim/armor.hpp"
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

struct ScanResult
{
  double yaw;
  double pitch;
};

struct ScanState
{
  double start_angle = 0.0;
  double scan_cmd_angle = 0.0;
  double scan_t = 0.0;
  bool use_omni_scan = false;
};

class Perceptron
{
public:
  using LeftImageReader =
    std::function<bool(cv::Mat &, std::chrono::steady_clock::time_point &)>;
  using LeftImageClearer = std::function<void()>;

  Perceptron(
    LeftImageReader left_reader, LeftImageClearer left_clearer, io::USBCamera * right_cam,
    const std::string & config_path);

  void clear_side_buffers();
  bool detect_left(DetectionResult & result);
  bool detect_right(DetectionResult & result);
  ScanResult scan(double current_yaw, double dt, ScanState & state) const;
  std::optional<DetectionResult> choose_switch_candidate(
    const std::optional<DetectionResult> & left_candidate,
    const std::optional<DetectionResult> & right_candidate) const;

private:
  LeftImageReader left_reader_;
  LeftImageClearer left_clearer_;
  io::USBCamera * right_cam_;

  std::shared_ptr<auto_aim::YOLO> yolo_left_;
  std::shared_ptr<auto_aim::YOLO> yolo_right_;

  auto_aim::Color enemy_color_;
  int mode_ = 1;
  double img_width_ = 0.0;
  double img_height_ = 0.0;
  double new_fov_h_ = 0.0;
  double new_fov_v_ = 0.0;

  ScanResult omni_scan(double dt, ScanState & state) const;
  ScanResult short_lost_scan(double start_yaw_deg, double dt, ScanState & state) const;

  bool filter_armors(std::list<auto_aim::Armor> & armors) const;
  void set_priority(std::list<auto_aim::Armor> & armors) const;
  void sort_armors(std::list<auto_aim::Armor> & armors) const;
  Eigen::Vector2d delta_angle(
    const std::list<auto_aim::Armor> & armors, const std::string & camera) const;
};

}  // namespace omniperception

#endif
