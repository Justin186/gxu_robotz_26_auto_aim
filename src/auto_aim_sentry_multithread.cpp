#include <atomic>
#include <chrono>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <optional>
#include <thread>

#include "io/camera.hpp"
#include "io/ros2/gimbal_node.hpp"
#include "io/usbcamera/usbcamera.hpp"
#include "tasks/auto_aim/planner/planner.hpp"
#include "tasks/auto_aim/solver.hpp"
#include "tasks/auto_aim/tracker.hpp"
#include "tasks/auto_aim/yolo.hpp"
#include "tasks/omniperception/decider.hpp"
#include "tasks/omniperception/perceptron.hpp"
#include "tools/exiter.hpp"
#include "tools/math_tools.hpp"
#include "tools/recorder.hpp"
#include "tools/thread_safe_queue.hpp"

using namespace std::chrono_literals;

const std::string keys =
  "{help h usage ? |                        | output help}"
  "{fps            | false                  | print yolo fps}"
  "{v              | true                   | record main camera video}"
  "{@config-path   | configs/sentry.yaml | yaml config path}";

int main(int argc, char * argv[])
{
  tools::Exiter exiter;

  cv::CommandLineParser cli(argc, argv, keys);
  auto config_path = cli.get<std::string>(0);
  const bool print_fps = cli.get<bool>("fps");
  const bool record_video = cli.get<bool>("v");
  if (cli.has("help") || config_path.empty()) {
    cli.printMessage();
    return 0;
  }

  std::optional<tools::Recorder> recorder;
  if (record_video) recorder.emplace(30);

  io::GimbalNode gimbal(config_path);
  io::Camera camera(config_path);
  io::USBCamera usb_cam_right("video0", config_path);
  usb_cam_right.device_name = "right";

  auto_aim::YOLO yolo(config_path, false);
  auto_aim::Solver solver(config_path);
  auto_aim::Tracker tracker(config_path, solver);
  auto_aim::Planner planner(config_path);
  omniperception::Decider decider(config_path);
  omniperception::Perceptron perceptron(
    [&](cv::Mat & img, std::chrono::steady_clock::time_point & ts) {
      return gimbal.get_image(img, ts);
    },
    [&]() { gimbal.clear_image(); }, &usb_cam_right, config_path);
  perceptron.set_fps_enabled(print_fps);

  tools::ThreadSafeQueue<std::optional<auto_aim::Target>, true> target_queue(1);
  target_queue.push(std::nullopt);

  std::atomic<bool> quit = false;
  // 主线程只负责更新模式，控制线程按模式执行
  std::atomic<omniperception::Decider::OmniMode> omni_mode{
    omniperception::Decider::OmniMode::tracking};
  std::atomic<int> main_lost_count = 0;

  auto plan_thread = std::thread([&]() {
    auto last_control_time = std::chrono::steady_clock::now();
    auto last_mode = decider.mode();
    std::optional<io::Command> last_scan_command;
    double last_scan_yaw_vel = 0.0;
    double last_scan_pitch_vel = 0.0;

    while (!quit) {
      auto target = target_queue.front();
      auto gs = gimbal.state();
      auto now = std::chrono::steady_clock::now();
      const double dt = tools::delta_time(now, last_control_time);
      last_control_time = now;

      const auto requested_mode = omni_mode.load();
      auto current_mode = decider.mode();

      // 外层只负责请求 tracking / scan，不覆盖 Decider 内部产生的 switching
      if (requested_mode == omniperception::Decider::OmniMode::tracking &&
          current_mode != omniperception::Decider::OmniMode::tracking) {
        decider.set_mode(omniperception::Decider::OmniMode::tracking);
        current_mode = decider.mode();
      } else if (
        requested_mode == omniperception::Decider::OmniMode::scan &&
        current_mode == omniperception::Decider::OmniMode::tracking) {
        decider.set_mode(omniperception::Decider::OmniMode::scan);
        current_mode = decider.mode();
      }

      // 只有真正切回 tracking 时才清理一次侧向缓存
      if (current_mode == omniperception::Decider::OmniMode::tracking &&
          last_mode != omniperception::Decider::OmniMode::tracking) {
        perceptron.clear_side_buffers();
      }
      perceptron.set_enabled(current_mode == omniperception::Decider::OmniMode::scan);

      if (current_mode == omniperception::Decider::OmniMode::tracking) {
        last_scan_command.reset();
        last_scan_yaw_vel = 0.0;
        last_scan_pitch_vel = 0.0;
        auto plan = planner.plan(target, gs.bullet_speed, gs.yaw, gs.pitch);
        gimbal.set_aim_status(true);
        gimbal.send(
          plan.control, plan.fire, plan.yaw, plan.yaw_vel, plan.yaw_acc, -plan.pitch,
          -plan.pitch_vel, -plan.pitch_acc);
      } else {
        gimbal.set_aim_status(false);

        auto command = decider.decide(gs.yaw, gs.pitch, dt, perceptron);
        current_mode = decider.mode();
        if (command.control) {
          double yaw_vel = 0.0;
          double yaw_acc = 0.0;
          double pitch_vel = 0.0;
          double pitch_acc = 0.0;

          if (
            current_mode == omniperception::Decider::OmniMode::scan &&
            last_scan_command.has_value() && dt > 1e-4) {
            yaw_vel = tools::limit_rad(command.yaw - last_scan_command->yaw) / dt;
            pitch_vel = (command.pitch - last_scan_command->pitch) / dt;
            yaw_acc = (yaw_vel - last_scan_yaw_vel) / dt;
            pitch_acc = (pitch_vel - last_scan_pitch_vel) / dt;
          }

          gimbal.send(
            true, command.shoot, command.yaw, yaw_vel, yaw_acc, command.pitch, pitch_vel,
            pitch_acc);

          if (current_mode == omniperception::Decider::OmniMode::scan) {
            last_scan_command = command;
            last_scan_yaw_vel = yaw_vel;
            last_scan_pitch_vel = pitch_vel;
          } else {
            last_scan_command.reset();
            last_scan_yaw_vel = 0.0;
            last_scan_pitch_vel = 0.0;
          }
        } else {
          last_scan_command.reset();
          last_scan_yaw_vel = 0.0;
          last_scan_pitch_vel = 0.0;
        }
      }

      omni_mode.store(current_mode);
      last_mode = current_mode;

      std::this_thread::sleep_for(2ms);
    }
  });

  cv::Mat img;
  std::chrono::steady_clock::time_point timestamp;
  auto main_fps_time = std::chrono::steady_clock::now();
  int main_fps_count = 0;

  while (!exiter.exit()) {
    camera.read(img, timestamp);

    auto q = gimbal.q(timestamp);
    solver.set_R_gimbal2world(q);
    if (record_video && recorder.has_value()) {
      recorder->record(img, q, timestamp);
    }

    auto armors = yolo.detect(img);
    if (print_fps) {
      main_fps_count++;
      auto now = std::chrono::steady_clock::now();
      auto elapsed = std::chrono::duration<double>(now - main_fps_time).count();
      if (elapsed >= 1.0) {
        std::cout << "[FPS] main_yolo: " << main_fps_count / elapsed << std::endl;
        main_fps_count = 0;
        main_fps_time = now;
      }
    }

    auto targets = tracker.track(armors, timestamp);

    if (!targets.empty()) {
      // 主相机一旦重新拿到目标，就立刻回到 tracking 模式
      omni_mode = omniperception::Decider::OmniMode::tracking;
      main_lost_count = 0;
      target_queue.push(targets.front());
    } else {
      main_lost_count++;
      // 主相机连续丢失足够多帧后，才切到 scan 让全向接管
      if (main_lost_count.load() >= 25 &&
          omni_mode.load() == omniperception::Decider::OmniMode::tracking) {
        omni_mode = omniperception::Decider::OmniMode::scan;
      }
      target_queue.push(std::nullopt);
    }
  }

  quit = true;
  if (plan_thread.joinable()) plan_thread.join();
  gimbal.send(false, false, 0, 0, 0, 0, 0, 0);
  return 0;
}
