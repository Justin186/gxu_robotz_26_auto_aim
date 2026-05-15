#include <fmt/core.h>

#include <atomic>
#include <chrono>
#include <nlohmann/json.hpp>
#include <opencv2/opencv.hpp>
#include <thread>
#include <mutex>
#include <optional>
#include <deque>
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
#include "tools/plotter.hpp"
#include "tools/thread_safe_queue.hpp"
#include "tools/yaml.hpp"

using namespace std::chrono_literals;

const std::string keys =
  "{help h usage ? | | 输出命令行参数说明}"
  "{ip             | 192.168.1.18 | Rerun 查看器的IP地址}"
  "{f              | true         | 是否开火}"
  "{imshow         | true         | 是否显示图像窗口}"
  "{rerun          | false        | 是否将数据记录到Rerun}"
  "{@config-path   | configs/example.yaml | 位置参数，yaml配置文件路径 }";

int main(int argc, char * argv[])
{
  tools::Exiter exiter;

  cv::CommandLineParser cli(argc, argv, keys);
  auto config_path = cli.get<std::string>(0);
  auto rerun_ip = cli.get<std::string>("ip");
  auto fire = cli.get<bool>("f");
  auto imshow = cli.get<bool>("imshow");
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

  io::Gimbal gimbal(config_path);
  io::Camera camera(config_path);

  auto_buff::Buff_Detector detector(config_path);
  auto_buff::Solver solver(config_path);
  auto_buff::SmallTarget target;
  auto_buff::Aimer aimer(config_path);

  auto yaml = tools::load(config_path);
  auto R_gimbal2imubody_data = tools::read<std::vector<double>>(yaml, "R_gimbal2imubody");
  Eigen::Matrix<double, 3, 3, Eigen::RowMajor> R_gimbal2imubody(R_gimbal2imubody_data.data());

  tools::ThreadSafeQueue<std::optional<auto_buff::SmallTarget>, true> target_queue(1);
  target_queue.push(std::nullopt);

  std::mutex shared_q_mutex;
  Eigen::Quaterniond shared_q = Eigen::Quaterniond::Identity();
  bool shared_q_ready = false;

  std::atomic<bool> quit = false;

  std::thread plan_thread([&]() {
    std::deque<bool> fire_history;
    const size_t history_max_size = tools::read<size_t>(yaml, "fire_duty_window", 500);

    size_t rerun_counter = 0;
    const size_t rerun_interval = 4;

    while (!quit) {
      auto opt_target = target_queue.front();

      Eigen::Quaterniond q_gimbal;
      {
        std::lock_guard<std::mutex> lock(shared_q_mutex);
        q_gimbal = shared_q_ready ? shared_q : Eigen::Quaterniond::Identity();
      }

      Eigen::Matrix3d R_imubody2world = q_gimbal.toRotationMatrix();
      Eigen::Matrix3d R_gimbal2world = R_imubody2world * R_gimbal2imubody;

      // compute plan (use a copy/default when no target)
      auto plan = aimer.mpc_aim(opt_target.value_or(auto_buff::SmallTarget()), std::chrono::steady_clock::now(), gimbal.state(), true);

      gimbal.send(
        plan.control, plan.fire && fire,
        plan.v_yaw, plan.yaw_vel, plan.yaw_acc,
        plan.v_pitch, plan.pitch_vel, plan.pitch_acc);

      bool fired = plan.fire && fire;
      fire_history.push_back(fired);
      if (fire_history.size() > history_max_size) fire_history.pop_front();
      double fire_duty = 0.0;
      for (bool f : fire_history) if (f) fire_duty += 1.0;
      if (!fire_history.empty()) fire_duty /= fire_history.size();

      bool do_rerun = rerun && (rerun_counter % rerun_interval == 0);

      if (do_rerun) {
        rec->log("world/gimbal",
          rerun::Transform3D(
            rerun::Vec3D{0.0f, 0.0f, 0.0f},
            rerun::Mat3x3({
              (float)R_gimbal2world(0,0), (float)R_gimbal2world(1,0), (float)R_gimbal2world(2,0),
              (float)R_gimbal2world(0,1), (float)R_gimbal2world(1,1), (float)R_gimbal2world(2,1),
              (float)R_gimbal2world(0,2), (float)R_gimbal2world(1,2), (float)R_gimbal2world(2,2)
            })
          ),
          rerun::TransformAxes3D(0.5)
        );

        rec->log("yaw/plan_yaw", rerun::Scalars(plan.yaw));
        rec->log("pitch/plan_pitch", rerun::Scalars(plan.pitch));
        rec->log("yaw/gimbal_yaw", rerun::Scalars((float)gimbal.state().yaw));
        rec->log("pitch/gimbal_pitch", rerun::Scalars((float)gimbal.state().pitch));
        rec->log("fire/plan_fire", rerun::Scalars(plan.fire ? 1.0f : 0.0f));
        rec->log("fire/duty_cycle", rerun::Scalars((float)fire_duty));
      }

      if (opt_target.has_value()) {
        auto &t = opt_target.value();
        auto x = t.ekf_x();
        if (do_rerun) {
          rec->log("scalar/buff/R_yaw", rerun::Scalars((float)x[0]));
          rec->log("scalar/buff/R_pitch", rerun::Scalars((float)x[2]));
          rec->log("scalar/buff/R_dis", rerun::Scalars((float)x[3]));
          rec->log("scalar/buff/yaw", rerun::Scalars((float)(x[4] * 57.3)));
          rec->log("scalar/buff/angle", rerun::Scalars((float)(x[5] * 57.3)));
        }
      } else {
        if (do_rerun) {
          rec->log("world/target/clear", rerun::Clear::FLAT);
        }
      }

      rerun_counter++;
      std::this_thread::sleep_for(5ms);
    }
  });

  cv::Mat img;
  Eigen::Quaterniond q;
  std::chrono::steady_clock::time_point t;

  while (!exiter.exit()) {
    camera.read(img, t);
    q = gimbal.q(t);
    auto gs = gimbal.state();

    {
      std::lock_guard<std::mutex> lock(shared_q_mutex);
      shared_q = q;
      shared_q_ready = true;
    }

    solver.set_R_gimbal2world(q);
    auto power_runes = detector.detect(img);
    solver.solve(power_runes);
    target.get_target(power_runes, t);

    target_queue.push(target);

    if (power_runes.has_value()) {
      const auto & p = power_runes.value();
      for (int i = 0; i < 4; i++) tools::draw_point(img, p.target().points[i]);
      tools::draw_point(img, p.target().center, {0, 0, 255}, 3);
      tools::draw_point(img, p.r_center, {0, 0, 255}, 3);
    }

    if (!target.is_unsolve()) {
      auto Rxyz_in_world_now = target.point_buff2world(Eigen::Vector3d(0.0, 0.0, 0.0));
      auto image_points = solver.reproject_buff(Rxyz_in_world_now, target.ekf_x()[4], target.ekf_x()[5]);
      tools::draw_points(img, std::vector<cv::Point2f>(image_points.begin(), image_points.begin() + 4), {0, 255, 0});
      tools::draw_points(img, std::vector<cv::Point2f>(image_points.begin() + 4, image_points.end()), {0, 255, 0});
    }

    if (imshow) {
      cv::resize(img, img, {}, 0.5, 0.5);
      cv::imshow("result", img);
    }

    if (rerun) {
      static auto last_t = std::chrono::steady_clock::now();
      auto now = std::chrono::steady_clock::now();
      float fps = 1.0f / std::chrono::duration<float>(now - last_t).count();
      last_t = now;
      rec->log("scalar/fps", rerun::Scalars(fps));
    }

    auto key = cv::waitKey(1);
    if (key == 'q') break;
  }

  quit = true;
  if (plan_thread.joinable()) plan_thread.join();
  gimbal.send(false, false, 0, 0, 0, 0, 0, 0);

  return 0;
}
