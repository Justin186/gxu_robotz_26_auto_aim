#include <fmt/format.h>

#include <string>
#include <nlohmann/json.hpp>
#include <rerun.hpp>

#include "io/camera.hpp"
#include "io/gimbal/gimbal.hpp"
#include "tasks/auto_buff/buff_aimer.hpp"
#include "tasks/auto_buff/buff_detector.hpp"
#include "tasks/auto_buff/buff_solver.hpp"
#include "tasks/auto_buff/buff_target.hpp"
#include "tasks/auto_buff/buff_type.hpp"
#include "tools/exiter.hpp"
#include "tools/img_tools.hpp"
#include "tools/logger.hpp"
#include "tools/math_tools.hpp"
#include "tools/recorder.hpp"
#include "tools/trajectory.hpp"

// 定义命令行参数
const std::string keys =
  "{help h usage ? |                        | 输出命令行参数说明}"
  "{ip             | 192.168.1.18           | Rerun 查看器的IP地址}"
  "{rerun          | false                  | 是否将数据记录到Rerun}"
  "{@config-path   | configs/sentry.yaml    | yaml配置文件路径 }";

int main(int argc, char * argv[])
{
  // 读取命令行参数
  cv::CommandLineParser cli(argc, argv, keys);
  auto config_path = cli.get<std::string>(0);
  auto rerun_ip = cli.get<std::string>("ip");
  auto rerun = cli.get<bool>("rerun");

  if (cli.has("help") || config_path.empty()) {
    cli.printMessage();
    return 0;
  }

  std::optional<rerun::RecordingStream> rec; 
  if (rerun) {
    rec.emplace("gxu_auto_buff_debug");
    rec->connect_grpc("rerun+http://" + rerun_ip + ":9876/proxy").exit_on_failure();
  }

  // 初始化录制器、退出器
  tools::Recorder recorder;
  tools::Exiter exiter;

  // 初始化云台、相机
  io::Gimbal gimbal(config_path);
  io::Camera camera(config_path);

  // 初始化识别器、解算器、追踪器、瞄准器
  auto_buff::Buff_Detector detector(config_path);
  auto_buff::Solver solver(config_path);
  auto_buff::SmallTarget target;
  // auto_buff::BigTarget target;
  auto_buff::Aimer aimer(config_path);

  cv::Mat img;
  Eigen::Quaterniond q;
  std::chrono::steady_clock::time_point t;

  size_t rerun_counter = 0;
  const size_t rerun_interval = 4;

  while (!exiter.exit()) {
    camera.read(img, t);
    q = gimbal.q(t);
    auto gs = gimbal.state();

    // -------------- 打符核心逻辑 --------------

    solver.set_R_gimbal2world(q);

    auto power_runes = detector.detect(img);

    solver.solve(power_runes);

    target.get_target(power_runes, t);

    auto target_copy = target;

    auto plan = aimer.mpc_aim(target_copy, t, gs, true);

    gimbal.send(
      plan.control, plan.fire, plan.v_yaw, plan.yaw_vel, plan.yaw_acc, plan.v_pitch, plan.pitch_vel,
      plan.pitch_acc);
    // -------------- 调试输出 --------------

    bool do_rerun = rerun && (rerun_counter % rerun_interval == 0);

    if (do_rerun) {
      if (power_runes.has_value()) {
        const auto & p = power_runes.value();
        rec->log("buff/R_yaw", rerun::Scalars(p.ypd_in_world[0]));
        rec->log("buff/R_pitch", rerun::Scalars(p.ypd_in_world[1]));
        rec->log("buff/R_dis", rerun::Scalars(p.ypd_in_world[2]));
        rec->log("buff/yaw", rerun::Scalars(p.ypr_in_world[0] * 57.3));
        rec->log("buff/pitch", rerun::Scalars(p.ypr_in_world[1] * 57.3));
        rec->log("buff/roll", rerun::Scalars(p.ypr_in_world[2] * 57.3));
      }

      if (!target.is_unsolve()) {
        Eigen::VectorXd x = target.ekf_x();
        rec->log("target/R_yaw", rerun::Scalars(x[0]));
        rec->log("target/R_V_yaw", rerun::Scalars(x[1]));
        rec->log("target/R_pitch", rerun::Scalars(x[2]));
        rec->log("target/R_dis", rerun::Scalars(x[3]));
        rec->log("target/yaw", rerun::Scalars(x[4] * 57.3));

        rec->log("target/angle", rerun::Scalars(x[5] * 57.3));
        if (x.size() >= 10) {
          rec->log("target/spd", rerun::Scalars(x[6]));
          rec->log("target/a", rerun::Scalars(x[7]));
          rec->log("target/w", rerun::Scalars(x[8]));
          rec->log("target/fi", rerun::Scalars(x[9]));
          rec->log("target/spd0", rerun::Scalars(target.spd));
        } else {
          rec->log("target/spd", rerun::Scalars(x[6] * 57.3));
        }
      }

      // 云台响应情况
      rec->log("gimbal/yaw", rerun::Scalars(gs.yaw * 57.3));
      rec->log("gimbal/pitch", rerun::Scalars(gs.pitch * 57.3));
      rec->log("gimbal/yaw_vel", rerun::Scalars(gs.yaw_vel * 57.3));
      rec->log("gimbal/pitch_vel", rerun::Scalars(gs.pitch_vel * 57.3));

      if (plan.control) {
        rec->log("plan/yaw", rerun::Scalars(plan.yaw * 57.3));
        rec->log("plan/pitch", rerun::Scalars(plan.pitch * 57.3));
        rec->log("plan/yaw_vel", rerun::Scalars(plan.yaw_vel * 57.3));
        rec->log("plan/pitch_vel", rerun::Scalars(plan.pitch_vel * 57.3));
        rec->log("plan/yaw_acc", rerun::Scalars(plan.yaw_acc * 57.3));
        rec->log("plan/pitch_acc", rerun::Scalars(plan.pitch_acc * 57.3));
        rec->log("plan/shoot", rerun::Scalars(plan.fire ? 1.0 : 0.0));
      }
    }

    if (!target.is_unsolve()) {
      auto & p = power_runes.value();
      for (int i = 0; i < 4; i++) tools::draw_point(img, p.target().points[i]);
      tools::draw_point(img, p.target().center, {0, 0, 255}, 3);
      tools::draw_point(img, p.r_center, {0, 0, 255}, 3);

      auto Rxyz_in_world_now = target.point_buff2world(Eigen::Vector3d(0.0, 0.0, 0.0));
      auto image_points =
        solver.reproject_buff(Rxyz_in_world_now, target.ekf_x()[4], target.ekf_x()[5]);
      tools::draw_points(
        img, std::vector<cv::Point2f>(image_points.begin(), image_points.begin() + 4), {0, 255, 0});
      tools::draw_points(
        img, std::vector<cv::Point2f>(image_points.begin() + 4, image_points.end()), {0, 255, 0});

      double dangle = target.ekf_x()[5] - target_copy.ekf_x()[5];
      auto Rxyz_in_world_pre = target.point_buff2world(Eigen::Vector3d(0.0, 0.0, 0.0));
      image_points =
        solver.reproject_buff(Rxyz_in_world_pre, target_copy.ekf_x()[4], target_copy.ekf_x()[5]);
      tools::draw_points(
        img, std::vector<cv::Point2f>(image_points.begin(), image_points.begin() + 4), {255, 0, 0});
      tools::draw_points(
        img, std::vector<cv::Point2f>(image_points.begin() + 4, image_points.end()), {255, 0, 0});
    }

    cv::resize(img, img, {}, 0.5, 0.5);
    cv::imshow("result", img);

    rerun_counter++;

    auto key = cv::waitKey(1);
    if (key == 'q') break;
  }

  return 0;
}
