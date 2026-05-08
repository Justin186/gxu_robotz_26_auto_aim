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
#include "tasks/omniperception/decider.hpp"
#include "tasks/omniperception/perceptron.hpp"
#include "tools/exiter.hpp"
#include "tools/img_tools.hpp"
#include "tools/math_tools.hpp"
#include "tools/thread_safe_queue.hpp"

using namespace std::chrono_literals;

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

  tools::ThreadSafeQueue<std::optional<auto_aim::Target>, true> target_queue(1);
  target_queue.push(std::nullopt);

  std::atomic<bool> quit = false;
  // 主线程只负责更新高层模式，控制线程按模式执行
  std::atomic<omniperception::Decider::OmniMode> omni_mode{
    omniperception::Decider::OmniMode::tracking};
  std::atomic<int> main_lost_count = 0;

  auto plan_thread = std::thread([&]() {
    auto last_control_time = std::chrono::steady_clock::now();

    while (!quit) {
      auto target = target_queue.front();
      auto gs = gimbal.state();
      auto now = std::chrono::steady_clock::now();
      const double dt = tools::delta_time(now, last_control_time);
      last_control_time = now;

      decider.set_mode(omni_mode.load());

      // 每轮先把主线程更新的模式同步给全向决策器
      // tracking 模式下，只走主相机自瞄闭环
      if (decider.mode() == omniperception::Decider::OmniMode::tracking) {
        decider.reset();
        perceptron.clear_side_buffers();

        auto plan = planner.plan(target, gs.bullet_speed, gs.yaw, gs.pitch);
        gimbal.set_aim_status(true);
        gimbal.send(
          plan.control, plan.fire, plan.yaw, plan.yaw_vel, plan.yaw_acc, -plan.pitch,
          -plan.pitch_vel, -plan.pitch_acc);
      } else {
        // scan / switching 模式统一交给全向决策器处理
        gimbal.set_aim_status(false);

        auto command = decider.decide(gs.yaw, gs.pitch, dt, perceptron);
        if (command.control) {
          gimbal.send(true, command.shoot, command.yaw, 0, 0, command.pitch, 0, 0);
        }
      }

      std::this_thread::sleep_for(2ms);
    }
  });

  cv::Mat img;
  std::chrono::steady_clock::time_point timestamp;
  auto last_fps_time = std::chrono::steady_clock::now();
  int frame_count = 0;

  double read_sum_ms = 0.0, read_max_ms = 0.0;
  double q_sum_ms = 0.0, q_max_ms = 0.0;
  double yolo_sum_ms = 0.0, yolo_max_ms = 0.0;
  double track_sum_ms = 0.0, track_max_ms = 0.0;
  double fps = 0.0;

  while (!exiter.exit()) {
    auto read_begin = std::chrono::steady_clock::now();
    camera.read(img, timestamp);
    auto read_end = std::chrono::steady_clock::now();
    const double read_ms = std::chrono::duration<double, std::milli>(read_end - read_begin).count();
    read_sum_ms += read_ms;
    read_max_ms = std::max(read_max_ms, read_ms);

    frame_count++;

    auto q_begin = std::chrono::steady_clock::now();
    auto q = gimbal.q(timestamp);
    auto q_end = std::chrono::steady_clock::now();
    const double q_ms = std::chrono::duration<double, std::milli>(q_end - q_begin).count();
    q_sum_ms += q_ms;
    q_max_ms = std::max(q_max_ms, q_ms);

    solver.set_R_gimbal2world(q);

    auto yolo_begin = std::chrono::steady_clock::now();
    auto armors = yolo.detect(img);
    auto yolo_end = std::chrono::steady_clock::now();
    const double yolo_ms = std::chrono::duration<double, std::milli>(yolo_end - yolo_begin).count();
    yolo_sum_ms += yolo_ms;
    yolo_max_ms = std::max(yolo_max_ms, yolo_ms);

    auto track_begin = std::chrono::steady_clock::now();
    auto targets = tracker.track(armors, timestamp);
    auto track_end = std::chrono::steady_clock::now();
    const double track_ms =
      std::chrono::duration<double, std::milli>(track_end - track_begin).count();
    track_sum_ms += track_ms;
    track_max_ms = std::max(track_max_ms, track_ms);

    if (!targets.empty()) {
      // 主相机一旦重新拿到目标，就立刻回到 tracking 模式
      omni_mode = omniperception::Decider::OmniMode::tracking;
      main_lost_count = 0;
      target_queue.push(targets.front());

      auto target = targets.front();
      for (const Eigen::Vector4d & xyza : target.armor_xyza_list()) {
        auto image_points =
          solver.reproject_armor(xyza.head(3), xyza[3], target.armor_type, target.name);
        tools::draw_points(img, image_points, {0, 255, 0});
      }

      Eigen::Vector4d aim_xyza = planner.debug_xyza;
      auto image_points =
        solver.reproject_armor(aim_xyza.head(3), aim_xyza[3], target.armor_type, target.name);
      tools::draw_points(img, image_points, {0, 0, 255});
    } else {
      main_lost_count++;
      // 主相机连续丢失足够多帧后，才切到 scan 让全向接管
      if (main_lost_count.load() >= 25 &&
          omni_mode.load() == omniperception::Decider::OmniMode::tracking) {
        omni_mode = omniperception::Decider::OmniMode::scan;
      }
      target_queue.push(std::nullopt);
    }

    auto now = std::chrono::steady_clock::now();
    if (std::chrono::duration<double>(now - last_fps_time).count() >= 1.0) {
      // 调试版额外统计主循环各阶段耗时，方便定位瓶颈
      const double count = static_cast<double>(frame_count);
      fps = count / std::chrono::duration<double>(now - last_fps_time).count();
      fmt::print(
        "FPS: {:.2f} | read avg/max: {:.2f}/{:.2f} ms | q avg/max: {:.2f}/{:.2f} ms "
        "| yolo avg/max: {:.2f}/{:.2f} ms | track avg/max: {:.2f}/{:.2f} ms\n",
        fps, read_sum_ms / count, read_max_ms, q_sum_ms / count, q_max_ms, yolo_sum_ms / count,
        yolo_max_ms, track_sum_ms / count, track_max_ms);

      frame_count = 0;
      last_fps_time = now;
      read_sum_ms = 0.0;
      read_max_ms = 0.0;
      q_sum_ms = 0.0;
      q_max_ms = 0.0;
      yolo_sum_ms = 0.0;
      yolo_max_ms = 0.0;
      track_sum_ms = 0.0;
      track_max_ms = 0.0;
    }

    tools::draw_text(img, fmt::format("FPS: {:.2f}", fps), {10, 30});
    auto key = cv::waitKey(1);
    if (key == 'q') break;
  }

  quit = true;
  if (plan_thread.joinable()) plan_thread.join();
  gimbal.send(false, false, 0, 0, 0, 0, 0, 0);
  return 0;
}
