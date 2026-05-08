#ifndef OMNIPERCEPTION__DECIDER_HPP
#define OMNIPERCEPTION__DECIDER_HPP

#include <Eigen/Dense>
#include <chrono>
#include <list>
#include <optional>
#include <unordered_map>

#include "detection.hpp"
#include "io/command.hpp"
#include "tasks/auto_aim/armor.hpp"

namespace omniperception
{
class Perceptron;

class Decider
{
public:
  // 全向感知高层模式：主相机跟踪、扫描搜敌、侧向切换
  enum class OmniMode
  {
    tracking,
    scan,
    switching
  };

  Decider(const std::string & config_path);

  void reset();
  void set_mode(OmniMode mode);
  OmniMode mode() const;
  // 在 scan / switching 模式下执行一次全向决策
  io::Command decide(
    double current_yaw, double current_pitch, double dt, Perceptron & perceptron);

  Eigen::Vector2d delta_angle(
    const std::list<auto_aim::Armor> & armors, const std::string & camera) const;

  bool armor_filter(std::list<auto_aim::Armor> & armors) const;
  void set_priority(std::list<auto_aim::Armor> & armors) const;

private:
  struct ScanResult
  {
    double yaw;
    double pitch;
  };

  struct ScanState
  {
    // start_angle: 特化扫描起始 yaw
    // scan_cmd_angle: 当前累计扫描角
    // scan_t: 当前扫描相位时间
    double start_angle = 0.0;
    double scan_cmd_angle = 0.0;
    double scan_t = 0.0;
    bool use_omni_scan = false;
  };

  void reset_runtime_state();
  bool process_detection(DetectionResult & result) const;
  void sort_armors(std::list<auto_aim::Armor> & armors) const;
  std::optional<DetectionResult> choose_switch_candidate(
    const std::optional<DetectionResult> & left_candidate,
    const std::optional<DetectionResult> & right_candidate) const;
  ScanResult scan(double current_yaw, double dt);
  ScanResult short_lost_scan(double start_yaw_deg, double dt);
  ScanResult omni_scan(double dt);

  int img_width_;
  int img_height_;
  double new_fov_h_;
  double new_fov_v_;
  int priority_mode_;

  auto_aim::Color enemy_color_;
  // 以下成员都属于全向扫描 / 切换状态机的运行时状态
  OmniMode mode_ = OmniMode::tracking;
  ScanState scan_state_;
  int left_seen_count_ = 0;
  int right_seen_count_ = 0;
  std::optional<DetectionResult> left_candidate_;
  std::optional<DetectionResult> right_candidate_;
  double switching_target_yaw_ = 0.0;
  double switching_target_pitch_ = 0.0;
  std::chrono::steady_clock::time_point switching_start_time_;
  std::chrono::steady_clock::time_point last_side_detect_time_;
  bool detect_left_next_ = true;
  std::chrono::milliseconds side_detect_interval_{25};
  std::chrono::milliseconds switching_timeout_{1200};
  int confirm_count_ = 5;

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
};

enum PriorityMode
{
  MODE_ONE = 1,
  MODE_TWO
};

}  // namespace omniperception

#endif
