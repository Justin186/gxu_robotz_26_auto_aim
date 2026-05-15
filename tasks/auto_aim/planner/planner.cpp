#include "planner.hpp"

#include <vector>

#include "tools/math_tools.hpp"
#include "tools/trajectory.hpp"
#include "tools/yaml.hpp"

using namespace std::chrono_literals;

namespace auto_aim
{
Planner::Planner(const std::string & config_path)
{
  auto yaml = tools::load(config_path);
  yaw_offset_ = tools::read<double>(yaml, "yaw_offset") / 57.3;
  pitch_offset_ = tools::read<double>(yaml, "pitch_offset") / 57.3;
  fire_thresh_ = tools::read<double>(yaml, "fire_thresh");
  max_armor_angle_ = tools::read<double>(yaml, "max_armor_angle", 30.0) / 57.3;
  decision_speed_ = tools::read<double>(yaml, "decision_speed");
  high_speed_delay_time_ = tools::read<double>(yaml, "high_speed_delay_time");
  low_speed_delay_time_ = tools::read<double>(yaml, "low_speed_delay_time");
  defult_bullet_speed_ = tools::read<double>(yaml, "defult_bullet_speed", 22);

  auto R_gimbal2imubody_data = tools::read<std::vector<double>>(yaml, "R_gimbal2imubody");
  R_gimbal2imubody_ = Eigen::Matrix<double, 3, 3, Eigen::RowMajor>(R_gimbal2imubody_data.data());

  setup_yaw_solver(config_path);
  setup_pitch_solver(config_path);
}

Plan Planner::plan(
  Target target, double bullet_speed, double current_yaw, double current_pitch, double yaw_offset,
  double pitch_offset)
{
  // 0. Check bullet speed
  if (bullet_speed < 10 || bullet_speed > 25) {
    bullet_speed = defult_bullet_speed_;
  }

  // 1. Predict fly_time
  Eigen::Vector3d xyz;
  auto min_dist = 1e10;
  for (auto & xyza : target.armor_xyza_list()) {
    auto dist = xyza.head<2>().norm();
    if (dist < min_dist) {
      min_dist = dist;
      xyz = xyza.head<3>();
    }
  }
  auto bullet_traj = tools::Trajectory(bullet_speed, min_dist, xyz.z());
  target.predict(bullet_traj.fly_time);

  // 2. Get trajectory
  double yaw0;
  Trajectory traj;
  double current_armor_yaw;
  try {
    yaw0 = aim(target, bullet_speed, tracking_id_)(0); // 这里会传入并更新物理帧的 tracking_id_
    current_armor_yaw = debug_xyza[3];
    Eigen::Vector4d final_aim_xyza = debug_xyza; // 记录真正的击打点，防止被下方的循环覆盖
    traj = get_trajectory(target, yaw0, bullet_speed);
    debug_xyza = final_aim_xyza; // 恢复真正的击打点供外部红框绘制
  } catch (const std::exception & e) {
    tools::logger()->warn("Unsolvable target {:.2f}", bullet_speed);
    return {false};
  }

  // 3. Solve yaw
  Eigen::VectorXd x0(2);
  x0 << traj(0, 0), traj(1, 0); // 恢复MPC原有的纯前馈平滑生成模式
  tiny_set_x0(yaw_solver_, x0);

  yaw_solver_->work->Xref = traj.block(0, 0, 2, HORIZON);
  tiny_solve(yaw_solver_);

  // 4. Solve pitch
  x0 << traj(2, 0), traj(3, 0);
  tiny_set_x0(pitch_solver_, x0);

  pitch_solver_->work->Xref = traj.block(2, 0, 2, HORIZON);
  tiny_solve(pitch_solver_);

  Plan plan;
  plan.control = true;

  plan.target_yaw = tools::limit_rad(traj(0, HALF_HORIZON) + yaw0);
  plan.target_pitch = traj(2, HALF_HORIZON);

  plan.yaw = tools::limit_rad(yaw_solver_->work->x(0, HALF_HORIZON) + yaw0);
  plan.yaw_vel = yaw_solver_->work->x(1, HALF_HORIZON);
  plan.yaw_acc = yaw_solver_->work->u(0, HALF_HORIZON);

  plan.pitch = pitch_solver_->work->x(0, HALF_HORIZON);
  plan.pitch_vel = pitch_solver_->work->x(1, HALF_HORIZON);
  plan.pitch_acc = pitch_solver_->work->u(0, HALF_HORIZON);

  // 补偿云台底层控制的稳态跟踪误差及弹道经验偏置，在此处外部加上
  // 从而使得 Rerun 中显示的 plan.yaw 依旧是纯净的目标轨迹，电控接收到的是带有稳态补偿的指令
  auto yaw_offset_from_gimbal = yaw_offset / 10.0 / 57.3;
  auto pitch_offset_from_gimbal = pitch_offset / 10.0 / 57.3;
  plan.v_yaw = tools::limit_rad(plan.yaw + yaw_offset_ + yaw_offset_from_gimbal);
  plan.v_pitch = plan.pitch + pitch_offset_ + pitch_offset_from_gimbal;

  auto shoot_offset_ = 1;
  auto center_yaw = std::atan2(target.ekf_x()[2], target.ekf_x()[0]);
  auto delta_angle = std::abs(tools::limit_rad(current_armor_yaw - center_yaw));

  double real_yaw_error = tools::limit_rad(std::abs(current_yaw - plan.target_yaw));
  double real_pitch_error = current_pitch - plan.target_pitch;

  plan.fire =
    target.maneuver_ticks > 0 ? false :
    std::hypot(
      traj(0, HALF_HORIZON + shoot_offset_) - yaw_solver_->work->x(0, HALF_HORIZON + shoot_offset_),
      traj(2, HALF_HORIZON + shoot_offset_) -
        pitch_solver_->work->x(0, HALF_HORIZON + shoot_offset_)) < fire_thresh_ &&
    delta_angle < max_armor_angle_;

  return plan;
}

Plan Planner::plan(
  std::optional<Target> target, double bullet_speed, double current_yaw, double current_pitch,
  double yaw_offset, double pitch_offset,
  std::optional<std::chrono::steady_clock::time_point> current_time)
{
  if (!target.has_value()) return {false};

  double delay_time =
    std::abs(target->ekf_x()[7]) > decision_speed_ ? high_speed_delay_time_ : low_speed_delay_time_;

  auto base_time = current_time.value_or(std::chrono::steady_clock::now());
  auto future = base_time + std::chrono::microseconds(int(delay_time * 1e6));

  target->predict(future);

  return plan(*target, bullet_speed, current_yaw, current_pitch, yaw_offset, pitch_offset);
}

void Planner::setup_yaw_solver(const std::string & config_path)
{
  auto yaml = tools::load(config_path);
  auto max_yaw_acc = tools::read<double>(yaml, "max_yaw_acc");
  auto Q_yaw = tools::read<std::vector<double>>(yaml, "Q_yaw");
  auto R_yaw = tools::read<std::vector<double>>(yaml, "R_yaw");

  Eigen::MatrixXd A{{1, DT}, {0, 1}};
  Eigen::MatrixXd B{{0}, {DT}};
  Eigen::VectorXd f{{0, 0}};
  Eigen::Matrix<double, 2, 1> Q(Q_yaw.data());
  Eigen::Matrix<double, 1, 1> R(R_yaw.data());
  tiny_setup(&yaw_solver_, A, B, f, Q.asDiagonal(), R.asDiagonal(), 1.0, 2, 1, HORIZON, 0);

  Eigen::MatrixXd x_min = Eigen::MatrixXd::Constant(2, HORIZON, -1e17);
  Eigen::MatrixXd x_max = Eigen::MatrixXd::Constant(2, HORIZON, 1e17);
  Eigen::MatrixXd u_min = Eigen::MatrixXd::Constant(1, HORIZON - 1, -max_yaw_acc);
  Eigen::MatrixXd u_max = Eigen::MatrixXd::Constant(1, HORIZON - 1, max_yaw_acc);
  tiny_set_bound_constraints(yaw_solver_, x_min, x_max, u_min, u_max);

  yaw_solver_->settings->max_iter = 10;
}

void Planner::setup_pitch_solver(const std::string & config_path)
{
  auto yaml = tools::load(config_path);
  auto max_pitch_acc = tools::read<double>(yaml, "max_pitch_acc");
  auto Q_pitch = tools::read<std::vector<double>>(yaml, "Q_pitch");
  auto R_pitch = tools::read<std::vector<double>>(yaml, "R_pitch");

  Eigen::MatrixXd A{{1, DT}, {0, 1}};
  Eigen::MatrixXd B{{0}, {DT}};
  Eigen::VectorXd f{{0, 0}};
  Eigen::Matrix<double, 2, 1> Q(Q_pitch.data());
  Eigen::Matrix<double, 1, 1> R(R_pitch.data());
  tiny_setup(&pitch_solver_, A, B, f, Q.asDiagonal(), R.asDiagonal(), 1.0, 2, 1, HORIZON, 0);

  Eigen::MatrixXd x_min = Eigen::MatrixXd::Constant(2, HORIZON, -1e17);
  Eigen::MatrixXd x_max = Eigen::MatrixXd::Constant(2, HORIZON, 1e17);
  Eigen::MatrixXd u_min = Eigen::MatrixXd::Constant(1, HORIZON - 1, -max_pitch_acc);
  Eigen::MatrixXd u_max = Eigen::MatrixXd::Constant(1, HORIZON - 1, max_pitch_acc);
  tiny_set_bound_constraints(pitch_solver_, x_min, x_max, u_min, u_max);

  pitch_solver_->settings->max_iter = 10;
}

Eigen::Matrix<double, 2, 1> Planner::aim(const Target & target, double bullet_speed, int & id_state)
{
  Eigen::Vector3d xyz;
  double yaw;
  auto target_armors = target.armor_xyza_list();
  auto center_yaw = std::atan2(target.ekf_x()[2], target.ekf_x()[0]);
  auto min_delta_angle = 1e10;
  int best_id = -1;

  for (size_t i = 0; i < target_armors.size(); i++) {
    auto & xyza = target_armors[i];
    auto delta_angle = std::abs(tools::limit_rad(xyza[3] - center_yaw));
    
    // 滞回机制：如果是当前正在跟踪的板子，赋予 0.08rad（约4.6°）的倾向性，防止目标抖动导致换板
    if (id_state == (int)i) {
      delta_angle -= 0.08;
    }

    if (delta_angle < min_delta_angle) {
      min_delta_angle = delta_angle;
      best_id = (int)i;
      xyz = xyza.head<3>();
      yaw = xyza[3];
    }
  }
  id_state = best_id; // 反馈更新选择的装甲板ID

  debug_xyza = Eigen::Vector4d(xyz.x(), xyz.y(), xyz.z(), yaw);

  auto azim = std::atan2(xyz.y(), xyz.x());
  auto dist = xyz.head<2>().norm();
  auto bullet_traj = tools::Trajectory(bullet_speed, dist, xyz.z());
  if (bullet_traj.unsolvable) throw std::runtime_error("Unsolvable bullet trajectory!");

  double yaw_world = tools::limit_rad(azim);
  double pitch_world = -bullet_traj.pitch;

  Eigen::Vector3d v_world = tools::ypd2xyz({yaw_world, -pitch_world, 1.0});
  Eigen::Vector3d v_gimbal = R_gimbal2imubody_.transpose() * v_world;
  Eigen::Vector3d ypd_gimbal = tools::xyz2ypd(v_gimbal);

  return {ypd_gimbal[0], ypd_gimbal[1]};
}

Trajectory Planner::get_trajectory(Target & target, double yaw0, double bullet_speed)
{
  Trajectory traj;
  int sim_id = tracking_id_; // 取当前真实帧跟踪的装甲板作为预测起点，并允许在预测中自然换面

  target.predict(-DT * (HALF_HORIZON + 1));
  auto yaw_pitch_last = aim(target, bullet_speed, sim_id);

  target.predict(DT);  // [0] = -HALF_HORIZON * DT -> [HHALF_HORIZON] = 0
  auto yaw_pitch = aim(target, bullet_speed, sim_id);

  for (int i = 0; i < HORIZON; i++) {
    target.predict(DT);
    auto yaw_pitch_next = aim(target, bullet_speed, sim_id); // sim_id 可能在未来某帧自动切换换板

    auto yaw_vel = tools::limit_rad(yaw_pitch_next(0) - yaw_pitch_last(0)) / (2 * DT);
    auto pitch_vel = (yaw_pitch_next(1) - yaw_pitch_last(1)) / (2 * DT);

    traj.col(i) << tools::limit_rad(yaw_pitch(0) - yaw0), yaw_vel, yaw_pitch(1), pitch_vel;

    yaw_pitch_last = yaw_pitch;
    yaw_pitch = yaw_pitch_next;
  }

  return traj;
}

}  // namespace auto_aim