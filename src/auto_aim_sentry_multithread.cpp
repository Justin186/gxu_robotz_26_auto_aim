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
  // 主线程只负责更新模式，控制线程按模式执行
  std::atomic<omniperception::Decider::OmniMode> omni_mode{
    omniperception::Decider::OmniMode::tracking};//原子变量
  std::atomic<int> main_lost_count = 0;//原子变量，防止自瞄和

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
        decider.reset();//侧向感知所以计数清零，设置模式为tracking
        perceptron.clear_side_buffers();//清空缓存

        auto plan = planner.plan(target, gs.bullet_speed, gs.yaw, gs.pitch);
        gimbal.set_aim_status(true);//gimbal.aim_detect_enemy_=true
        gimbal.send(
          plan.control, plan.fire, plan.yaw, plan.yaw_vel, plan.yaw_acc, -plan.pitch,
          -plan.pitch_vel, -plan.pitch_acc);
      } else {
        // scan / switching 模式统一交给全向决策器处理
        gimbal.set_aim_status(false);

        //综合非自瞄状态的全向决策并且返回控制角度。
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

  while (!exiter.exit()) {
    camera.read(img, timestamp);

    auto q = gimbal.q(timestamp);
    solver.set_R_gimbal2world(q);

    auto armors = yolo.detect(img);
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
