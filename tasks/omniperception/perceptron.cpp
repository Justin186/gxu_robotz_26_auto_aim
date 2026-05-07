#include "perceptron.hpp"

#include <cmath>
#include <opencv2/core/types.hpp>
#include <unordered_map>

#include <yaml-cpp/yaml.h>

#include "io/usbcamera/usbcamera.hpp"
#include "tasks/auto_aim/yolo.hpp"
#include "tools/math_tools.hpp"

namespace omniperception
{
namespace
{
using PriorityMap = std::unordered_map<auto_aim::ArmorName, auto_aim::ArmorPriority>;

const PriorityMap mode1 = {
  {auto_aim::ArmorName::one, auto_aim::ArmorPriority::second},
  {auto_aim::ArmorName::two, auto_aim::ArmorPriority::forth},
  {auto_aim::ArmorName::three, auto_aim::ArmorPriority::first},
  {auto_aim::ArmorName::four, auto_aim::ArmorPriority::first},
  {auto_aim::ArmorName::five, auto_aim::ArmorPriority::third},
  {auto_aim::ArmorName::sentry, auto_aim::ArmorPriority::third},
  {auto_aim::ArmorName::outpost, auto_aim::ArmorPriority::fifth},
  {auto_aim::ArmorName::base, auto_aim::ArmorPriority::fifth},
  {auto_aim::ArmorName::not_armor, auto_aim::ArmorPriority::fifth}};

const PriorityMap mode2 = {
  {auto_aim::ArmorName::two, auto_aim::ArmorPriority::first},
  {auto_aim::ArmorName::one, auto_aim::ArmorPriority::second},
  {auto_aim::ArmorName::three, auto_aim::ArmorPriority::second},
  {auto_aim::ArmorName::four, auto_aim::ArmorPriority::second},
  {auto_aim::ArmorName::five, auto_aim::ArmorPriority::second},
  {auto_aim::ArmorName::sentry, auto_aim::ArmorPriority::third},
  {auto_aim::ArmorName::outpost, auto_aim::ArmorPriority::third},
  {auto_aim::ArmorName::base, auto_aim::ArmorPriority::third},
  {auto_aim::ArmorName::not_armor, auto_aim::ArmorPriority::third}};
}  // namespace

Perceptron::Perceptron(
  LeftImageReader left_reader, LeftImageClearer left_clearer, io::USBCamera * right_cam,
  const std::string & config_path)
: left_reader_(std::move(left_reader)), left_clearer_(std::move(left_clearer)), right_cam_(right_cam)
{
  auto yaml = YAML::LoadFile(config_path);
  enemy_color_ =
    (yaml["enemy_color"].as<std::string>() == "red") ? auto_aim::Color::red : auto_aim::Color::blue;
  mode_ = yaml["mode"].as<int>();
  img_width_ = yaml["image_width"].as<double>();
  img_height_ = yaml["image_height"].as<double>();
  new_fov_h_ = yaml["new_fov_h"].as<double>();
  new_fov_v_ = yaml["new_fov_v"].as<double>();

  yolo_left_ = std::make_shared<auto_aim::YOLO>(config_path, false);
  yolo_right_ = std::make_shared<auto_aim::YOLO>(config_path, false);
}

void Perceptron::clear_side_buffers()
{
  if (left_clearer_) {
    left_clearer_();
  }
  if (right_cam_) {
    right_cam_->clear_buffer();
  }
}

bool Perceptron::detect_left(DetectionResult & result)
{
  cv::Mat img;
  std::chrono::steady_clock::time_point ts;
  if (!left_reader_ || !left_reader_(img, ts) || img.empty()) return false;

  auto armors = yolo_left_->detect(img);
  if (filter_armors(armors)) return false;
  set_priority(armors);//给所有识别到的装甲板设置优先级
  sort_armors(armors);//根据优先级和离中心距离排序

  auto angles = delta_angle(armors, "left");
  result.armors = std::move(armors);
  result.timestamp = ts;
  result.source = "left";
  result.delta_yaw = angles[0] / 57.3;
  result.delta_pitch = angles[1] / 57.3;
  return true;
}

bool Perceptron::detect_right(DetectionResult & result)
{
  if (!right_cam_) return false;

  cv::Mat img;
  std::chrono::steady_clock::time_point ts;
  if (!right_cam_->try_read(img, ts) || img.empty()) return false;

  auto armors = yolo_right_->detect(img);
  if (filter_armors(armors)) return false;
  set_priority(armors);
  sort_armors(armors);

  auto angles = delta_angle(armors, "right");
  result.armors = std::move(armors);
  result.timestamp = ts;
  result.source = "right";
  result.delta_yaw = angles[0] / 57.3;
  result.delta_pitch = angles[1] / 57.3;
  return true;
}

ScanResult Perceptron::omni_scan(double dt, ScanState & state) const
{
  double delta_angle = 60.0;
  double amplitude = 15.0;
  double period = 1.0;

  state.scan_cmd_angle += delta_angle * dt;
  double yaw = tools::limit_rad(state.scan_cmd_angle / 57.3);
  double pitch =
    tools::limit_rad(amplitude * std::sin(2 * M_PI * state.scan_t / period) / 57.3 - 0.15);

  state.scan_t += dt;
  if (state.scan_t >= period) state.scan_t -= period;

  return {yaw, pitch};
}

ScanResult Perceptron::short_lost_scan(double start_yaw_deg, double dt, ScanState & state) const
{
  double yaw_amplitude = 15.0;
  double yaw_period = 1.0;
  double pitch_amplitude = 15.0;
  double pitch_period = 0.75;

  state.scan_t += dt;
  if (state.scan_t >= 4.0) {
    state.use_omni_scan = true;
  }

  double yaw_deg = start_yaw_deg - yaw_amplitude * std::sin(2 * M_PI * state.scan_t / yaw_period);
  double yaw = tools::limit_rad(yaw_deg / 57.3);
  double pitch =
    tools::limit_rad(pitch_amplitude * std::sin(2 * M_PI * state.scan_t / pitch_period) / 57.3 + 0.1);

  return {yaw, pitch};
}

ScanResult Perceptron::scan(double current_yaw, double dt, ScanState & state) const
{
  if (state.scan_t == 0.0 && state.scan_cmd_angle == 0.0) {
    state.start_angle = current_yaw * 57.3;
    state.scan_cmd_angle = state.start_angle;
    state.use_omni_scan = false;
  }

  if (state.use_omni_scan) {
    return omni_scan(dt, state);
  }
  return short_lost_scan(state.start_angle, dt, state);
}

//过滤敌方颜色和工程
bool Perceptron::filter_armors(std::list<auto_aim::Armor> & armors) const
{
  if (armors.empty()) return true;

  armors.remove_if([&](const auto_aim::Armor & a) { return a.color != enemy_color_; });
  armors.remove_if([&](const auto_aim::Armor & a) { return a.name == auto_aim::ArmorName::five; });
  //armors.remove_if([&](const auto_aim::Armor & a) { return a.name == auto_aim::ArmorName::outpost; });
  return armors.empty();
}

//
void Perceptron::set_priority(std::list<auto_aim::Armor> & armors) const
{
  const PriorityMap & priority_map = (mode_ == 1) ? mode1 : mode2;
  for (auto & armor : armors) {
    armor.priority = priority_map.at(armor.name);
  }
}

//优先级相同的装甲板，离图像中心更近的优先
void Perceptron::sort_armors(std::list<auto_aim::Armor> & armors) const
{
  const cv::Point2f img_center(img_width_ * 0.5f, img_height_ * 0.5f);
  armors.sort([&img_center](const auto_aim::Armor & a, const auto_aim::Armor & b) {
    auto distance_1 = cv::norm(a.center - img_center);
    auto distance_2 = cv::norm(b.center - img_center);
    return distance_1 < distance_2;
  });

  armors.sort([](const auto_aim::Armor & a, const auto_aim::Armor & b) {
    return a.priority < b.priority;
  });
}

Eigen::Vector2d Perceptron::delta_angle(
  const std::list<auto_aim::Armor> & armors, const std::string & camera) const
{
  Eigen::Vector2d angles;
  if (camera == "left") {
    angles[0] = 62 + (new_fov_h_ / 2) - armors.front().center_norm.x * new_fov_h_;
    angles[1] = armors.front().center_norm.y * new_fov_v_ - new_fov_v_ / 2;
    return angles;
  }

  angles[0] = -62 + (new_fov_h_ / 2) - armors.front().center_norm.x * new_fov_h_;
  angles[1] = armors.front().center_norm.y * new_fov_v_ - new_fov_v_ / 2;
  return angles;
}

//左右都有装甲板，根据优先级和偏航角选择一个目标
std::optional<DetectionResult> Perceptron::choose_switch_candidate(
  const std::optional<DetectionResult> & left_candidate,
  const std::optional<DetectionResult> & right_candidate) const
{
  if (!left_candidate.has_value()) return right_candidate;
  if (!right_candidate.has_value()) return left_candidate;

  auto left_priority = left_candidate->armors.front().priority;
  auto right_priority = right_candidate->armors.front().priority;
  if (left_priority != right_priority) {
    return left_priority < right_priority ? left_candidate : right_candidate;
  }

  return std::abs(left_candidate->delta_yaw) < std::abs(right_candidate->delta_yaw) ? left_candidate
                                                                                     : right_candidate;
}

}  // namespace omniperception
