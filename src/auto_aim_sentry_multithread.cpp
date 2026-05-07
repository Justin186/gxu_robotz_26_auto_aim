#include <fmt/core.h>

#include <atomic>
#include <chrono>
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
#include "tasks/omniperception/perceptron.hpp"
#include "tools/exiter.hpp"
#include "tools/math_tools.hpp"
#include "tools/thread_safe_queue.hpp"

using namespace std::chrono_literals;

namespace
{
enum class OmniState
{
  scan,
  switching
};

bool tracker_is_active(const std::string & state)
{
  return state == "detecting" || state == "tracking" || state == "temp_lost";
}
}  // namespace

const std::string keys =
  "{help h usage ? |                        | output help}"
  "{@config-path   | configs/sentry.yaml | yaml config path}";

int main(int argc, char * argv[])
{
  tools::Exiter exiter;

  cv::CommandLineParser cli(argc, argv, keys);
  auto config_path = cli.get<std::string>(0);
  if (cli.has("help") || config_path.empty()) {
    cli.printMessage();
    return 0;
  }

  io::GimbalNode gimbal(config_path);
  io::Camera camera(config_path);
  io::USBCamera usb_cam_right("video0", config_path);//初始化usb摄像头
  usb_cam_right.device_name = "right";

  auto_aim::YOLO yolo(config_path, false);
  auto_aim::Solver solver(config_path);
  auto_aim::Tracker tracker(config_path, solver);
  auto_aim::Planner planner(config_path);
  omniperception::Perceptron perceptron(
    [&](cv::Mat & img, std::chrono::steady_clock::time_point & ts) { return gimbal.get_image(img, ts); },
    [&]() { gimbal.clear_image(); },
    &usb_cam_right, config_path);//初始化全向感知模块，ros相机也在这里初始化

  tools::ThreadSafeQueue<std::optional<auto_aim::Target>, true> target_queue(1);
  target_queue.push(std::nullopt);

  std::atomic<bool> quit = false;
  std::atomic<bool> main_tracker_active = false;
  std::atomic<int> main_lost_count = 0;

  auto plan_thread = std::thread([&]() {
    OmniState omni_state = OmniState::scan;
    omniperception::ScanState scan_state;
    int left_seen_count = 0;
    int right_seen_count = 0;
    std::optional<omniperception::DetectionResult> left_candidate;
    std::optional<omniperception::DetectionResult> right_candidate;
    double switching_target_yaw = 0.0;
    double switching_target_pitch = 0.0;

    auto last_control_time = std::chrono::steady_clock::now();

    while (!quit) {
      auto target = target_queue.front();
      auto gs = gimbal.state();
      auto now = std::chrono::steady_clock::now();
      double dt = tools::delta_time(now, last_control_time);
      last_control_time = now;

      if (main_tracker_active.load()) {
        omni_state = OmniState::scan;
        left_seen_count = 0;
        right_seen_count = 0;
        left_candidate.reset();
        right_candidate.reset();
        scan_state = {};
        perceptron.clear_side_buffers();

        auto plan = planner.plan(target, gs.bullet_speed, gs.yaw, gs.pitch);
        gimbal.set_aim_status(true);
        gimbal.send(
          plan.control, plan.fire, plan.yaw, plan.yaw_vel, plan.yaw_acc, -plan.pitch, -plan.pitch_vel,
          -plan.pitch_acc);
      } else {
        gimbal.set_aim_status(false);

        if (main_lost_count.load() >= 25 && omni_state == OmniState::scan) {
          omniperception::DetectionResult left_result;
          if (perceptron.detect_left(left_result)) {
            left_seen_count++;
            left_candidate = left_result;
          } else {
            left_seen_count = 0;
            left_candidate.reset();
          }

          omniperception::DetectionResult right_result;
          if (perceptron.detect_right(right_result)) {
            right_seen_count++;
            right_candidate = right_result;
          } else {
            right_seen_count = 0;
            right_candidate.reset();
          }

          std::optional<omniperception::DetectionResult> left_ready =
            left_seen_count >= 5 ? left_candidate : std::nullopt;
          std::optional<omniperception::DetectionResult> right_ready =
            right_seen_count >= 5 ? right_candidate : std::nullopt;

          auto best = perceptron.choose_switch_candidate(left_ready, right_ready);
          if (best.has_value()) {
            switching_target_yaw = tools::limit_rad(gs.yaw + best->delta_yaw);
            switching_target_pitch = tools::limit_rad(gs.pitch + best->delta_pitch);
            omni_state = OmniState::switching;
            gimbal.send(
              true, false, switching_target_yaw, 0, 0, switching_target_pitch, 0, 0);
          } else {
            auto scan_result = perceptron.scan(gs.yaw, dt, scan_state);
            gimbal.send(true, false, scan_result.yaw, 0, 0, scan_result.pitch, 0, 0);
          }
        } else if (omni_state == OmniState::switching) {
          constexpr double yaw_thresh = 3.0 / 57.3;
          constexpr double pitch_thresh = 3.0 / 57.3;

          if (std::abs(tools::limit_rad(gs.yaw - switching_target_yaw)) < yaw_thresh &&
              std::abs(gs.pitch - switching_target_pitch) < pitch_thresh) {
            omni_state = OmniState::scan;
            left_seen_count = 0;
            right_seen_count = 0;
            left_candidate.reset();
            right_candidate.reset();
            scan_state = {};
          }
        } else {
          left_seen_count = 0;
          right_seen_count = 0;
          left_candidate.reset();
          right_candidate.reset();
          scan_state = {};
        }
      }

      std::this_thread::sleep_for(10ms);
    }
  });

  cv::Mat img;
  std::chrono::steady_clock::time_point t;
  auto last_fps_time = std::chrono::steady_clock::now();
  int frame_count = 0;

  while (!exiter.exit()) {
    camera.read(img, t);
    frame_count++;

    auto now = std::chrono::steady_clock::now();
    if (std::chrono::duration<double>(now - last_fps_time).count() >= 1.0) {
      double fps = frame_count / std::chrono::duration<double>(now - last_fps_time).count();
      fmt::print("FPS: {:.2f}\n", fps);
      frame_count = 0;
      last_fps_time = now;
    }

    auto q = gimbal.q(t);
    solver.set_R_gimbal2world(q);

    auto armors = yolo.detect(img);
    auto targets = tracker.track(armors, t);
    main_tracker_active = tracker_is_active(tracker.state());
    if (!targets.empty()) {
      main_lost_count = 0;
      target_queue.push(targets.front());
    } else {
      main_lost_count++;
      target_queue.push(std::nullopt);
    }
  }

  quit = true;
  if (plan_thread.joinable()) plan_thread.join();
  gimbal.send(false, false, 0, 0, 0, 0, 0, 0);
  return 0;
}
