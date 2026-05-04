#ifndef AUTO_AIM__PLANNER_HPP
#define AUTO_AIM__PLANNER_HPP

#include <Eigen/Dense>
#include <list>
#include <optional>

#include "tasks/auto_aim/target.hpp"
#include "tinympc/tiny_api.hpp"

namespace auto_aim
{
constexpr double DT = 0.01;
constexpr int HALF_HORIZON = 50;
constexpr int HORIZON = HALF_HORIZON * 2;

using Trajectory = Eigen::Matrix<double, 4, HORIZON>;  // yaw, yaw_vel, pitch, pitch_vel

struct Plan
{
  bool control;
  bool fire;
  float target_yaw;
  float target_pitch;
  float yaw;
  float pitch;
  float yaw_vel;
  float yaw_acc;
  float pitch_vel;
  float pitch_acc;
  float v_yaw;
  float v_pitch;
};

class Planner
{
public:
  Eigen::Vector4d debug_xyza;
  Planner(const std::string & config_path);

  Plan plan(Target target, double bullet_speed, double current_yaw = 0.0, double current_pitch = 0.0);
  Plan plan(
    std::optional<Target> target, double bullet_speed, double current_yaw = 0.0,
    double current_pitch = 0.0,
    std::optional<std::chrono::steady_clock::time_point> current_time = std::nullopt);

private:
  double yaw_offset_;
  double pitch_offset_;
  double fire_thresh_;
  double max_armor_angle_;
  double low_speed_delay_time_, high_speed_delay_time_, decision_speed_;
  double defult_bullet_speed_;

  Eigen::Matrix3d R_gimbal2imubody_;
  TinySolver * yaw_solver_;
  TinySolver * pitch_solver_;

  int tracking_id_ = -1; // 记录当前物理帧跟踪的装甲板ID，用于提供滞回阈值

  void setup_yaw_solver(const std::string & config_path);
  void setup_pitch_solver(const std::string & config_path);

  Eigen::Matrix<double, 2, 1> aim(const Target & target, double bullet_speed, int & id_state);
  Eigen::Matrix<double, 2, 1> aim_center(const Target & target, double bullet_speed);
  Trajectory get_trajectory(Target & target, double yaw0, double bullet_speed);
};

}  // namespace auto_aim

#endif  // AUTO_AIM__PLANNER_HPP