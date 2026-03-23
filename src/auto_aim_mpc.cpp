#include <fmt/core.h>

#include <atomic>
#include <chrono>
#include <deque>
#include <nlohmann/json.hpp>
#include <opencv2/opencv.hpp>
#include <thread>

#include "io/camera.hpp"
#include "io/gimbal/gimbal.hpp"
#include "tasks/auto_aim/planner/planner.hpp"
#include "tasks/auto_aim/solver.hpp"
#include "tasks/auto_aim/tracker.hpp"
#include "tasks/auto_aim/yolo.hpp"
#include "tools/exiter.hpp"
#include "tools/img_tools.hpp"
#include "tools/math_tools.hpp"
#include "tools/plotter.hpp"
#include "tools/thread_safe_queue.hpp"
#include "tools/yaml.hpp"
#include "tools/recorder.hpp"

using namespace std::chrono_literals;

const std::string keys =
  "{help h usage ? |                        | 输出命令行参数说明}"
  "{f              | true                   | 是否开火}"
  "{rec            | false                  | 是否强制录制数据}"
  "{@config-path   | configs/hero.yaml      | 位置参数，yaml配置文件路径 }";

int main(int argc, char * argv[])
{
  tools::Exiter exiter;
  // tools::Plotter plotter;
  tools::Recorder recorder;

  cv::CommandLineParser cli(argc, argv, keys);
  auto config_path = cli.get<std::string>(0);
  auto fire = cli.get<bool>("f");
  auto record = cli.get<bool>("rec");
  if (cli.has("help") || config_path.empty()) {
    cli.printMessage();
    return 0;
  }

  io::Gimbal gimbal(config_path);
  io::Camera camera(config_path);

  auto_aim::YOLO yolo(config_path, false);
  auto_aim::Solver solver(config_path);
  auto_aim::Tracker tracker(config_path, solver);
  auto_aim::Planner planner(config_path);

  auto yaml = tools::load(config_path);
  auto R_gimbal2imubody_data = tools::read<std::vector<double>>(yaml, "R_gimbal2imubody");
  Eigen::Matrix<double, 3, 3, Eigen::RowMajor> R_gimbal2imubody(R_gimbal2imubody_data.data());
  auto t_pitchlink2gimbal_data = tools::read<std::vector<double>>(yaml, "t_pitchlink2gimbal");
  Eigen::Vector3d t_pitchlink2gimbal(t_pitchlink2gimbal_data.data());
  t_pitchlink2gimbal /= 1000.0; // mm to m

  auto fire_duty_window = tools::read<size_t>(yaml, "fire_duty_window", 500);

  tools::ThreadSafeQueue<std::optional<auto_aim::Target>, true> target_queue(1);
  target_queue.push(std::nullopt);

  std::atomic<bool> quit = false;
  auto plan_thread = std::thread([&]() {
    auto t0 = std::chrono::steady_clock::now();
    uint16_t last_bullet_count = 0;
    
    std::deque<bool> fire_history;
    const size_t history_max_size = fire_duty_window;

    while (!quit) {
      auto target = target_queue.front();
      auto gs = gimbal.state();
      auto plan = planner.plan(target, gs.bullet_speed, gs.yaw, gs.pitch);
      // auto plan = planner.plan(target, gs.bullet_speed);

      gimbal.send(
        plan.control, plan.fire && fire,
        plan.yaw, plan.yaw_vel, plan.yaw_acc,
        plan.pitch, plan.pitch_vel, plan.pitch_acc);

      auto fired = gs.bullet_count > last_bullet_count;
      last_bullet_count = gs.bullet_count;
    }
  });

  cv::Mat img;
  std::chrono::steady_clock::time_point t;
  auto last_fps_t = std::chrono::steady_clock::now();
  int frame_count = 0;

  while (!exiter.exit()) {
    camera.read(img, t);
    auto now = std::chrono::steady_clock::now();
    frame_count++;
    if (std::chrono::duration_cast<std::chrono::seconds>(now - last_fps_t).count() >= 10) {
      double fps = frame_count / std::chrono::duration<double>(now - last_fps_t).count();
      tools::logger()->info("FPS: {:.2f}", fps);
      frame_count = 0;
      last_fps_t = now;
    }
    
    auto q = gimbal.q(t);
    auto gs = gimbal.state();
    if (gimbal.mode() != io::GimbalMode::IDLE || record) {
      recorder.record(img, q, t);
    }

    solver.set_R_gimbal2world(q);
    auto armors = yolo.detect(img);
    auto targets = tracker.track(armors, t);
    if (!targets.empty())
      target_queue.push(targets.front());
    else
      target_queue.push(std::nullopt);

    auto key = cv::waitKey(1);
    if (key == 'q') break;
  }

  quit = true;
  if (plan_thread.joinable()) plan_thread.join();
  gimbal.send(false, false, 0, 0, 0, 0, 0, 0);

  return 0;
}
