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
#include "tools/logger.hpp"
#include "tools/math_tools.hpp"
#include "tools/plotter.hpp"
#include "tools/thread_safe_queue.hpp"
#include "tools/recorder.hpp"


using namespace std::chrono_literals;

struct PlannerInput
{
  std::optional<auto_aim::Target> target;
  double bullet_speed;
  double yaw;
  double pitch;
  std::chrono::steady_clock::time_point t;
};

const std::string keys =
  "{help h usage ? |                        | 输出命令行参数说明}"
  "{rec            | true                  | 是否录制数据}"
  "{@config-path   | configs/sentry.yaml | 位置参数，yaml配置文件路径 }";

int main(int argc, char * argv[])
{
  tools::Exiter exiter;
  tools::Plotter plotter;
  tools::Recorder recorder;


  cv::CommandLineParser cli(argc, argv, keys);
  auto config_path = cli.get<std::string>(0);
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

  tools::ThreadSafeQueue<PlannerInput, true> target_queue(1);

  std::atomic<bool> quit = false;
  auto plan_thread = std::thread([&]() {
    auto t0 = std::chrono::steady_clock::now();
    uint16_t last_bullet_count = 0;
    std::deque<double> latency_history;

    PlannerInput input;
    input.target = std::nullopt;
    input.bullet_speed = 22.0;
    input.yaw = 0.0;
    input.pitch = 0.0;
    input.t = t0;

    int plan_count = 0;

    while (!quit) {
      target_queue.pop(input);
      if (quit) break;

      auto now = std::chrono::steady_clock::now();
      const double planner_latency = tools::delta_time(now, input.t);
      latency_history.push_back(planner_latency);
      if (latency_history.size() > 100) latency_history.pop_front();
      plan_count++;

      if (plan_count % 50 == 0 && !latency_history.empty()) {
        double avg_latency = 0.0;
        for (const auto & v : latency_history) avg_latency += v;
        avg_latency /= static_cast<double>(latency_history.size());
        tools::logger()->info(
          "[MPC] planner_latency avg={:.2f}ms last={:.2f}ms", avg_latency * 1e3,
          planner_latency * 1e3);
      }

      if (planner_latency > 0.03) {
        tools::logger()->warn("[MPC] planner data is stale: {:.2f}ms", planner_latency * 1e3);
      }

      auto target = input.target;
      auto gs = gimbal.state();
      auto plan = planner.plan(target, input.bullet_speed, input.yaw, input.pitch, input.t);

      gimbal.send(
        plan.control, plan.fire, plan.v_yaw, plan.yaw_vel, plan.yaw_acc, -plan.v_pitch, -plan.pitch_vel,
        -plan.pitch_acc);

      auto fired = gs.bullet_count > last_bullet_count;
      last_bullet_count = gs.bullet_count;

      nlohmann::json data;
      data["t"] = tools::delta_time(std::chrono::steady_clock::now(), t0);

      data["gimbal_yaw"] = gs.yaw;
      data["gimbal_yaw_vel"] = gs.yaw_vel;
      data["gimbal_pitch"] = gs.pitch;
      data["gimbal_pitch_vel"] = gs.pitch_vel;

      data["target_yaw"] = plan.target_yaw;
      data["target_pitch"] = plan.target_pitch;

      data["plan_yaw"] = plan.yaw;
      data["plan_yaw_vel"] = plan.yaw_vel;
      data["plan_yaw_acc"] = plan.yaw_acc;

      data["plan_pitch"] = plan.pitch;
      data["plan_pitch_vel"] = plan.pitch_vel;
      data["plan_pitch_acc"] = plan.pitch_acc;

      data["fire"] = plan.fire ? 1 : 0;
      data["fired"] = fired ? 1 : 0;

      if (target.has_value()) {
        data["target_x"] = target->ekf_x()[0];   //x
        data["target_vx"] = target->ekf_x()[1];   //vx
        data["target_y"] = target->ekf_x()[2];   //y
        data["target_vy"] = target->ekf_x()[3];   //vy
        data["target_z"] = target->ekf_x()[4];   //z
        data["target_vz"] = target->ekf_x()[5];  //vz
      }

      if (target.has_value()) {
        data["w"] = target->ekf_x()[7];
        data["r"] = target->ekf_x()[8];
        data["l"] = target->ekf_x()[9];
      } else {
        data["w"] = 0.0;
        data["r"] = 0.0;
        data["l"] = 0.0;
      }

      plotter.plot(data);
    }
  });

  cv::Mat img;
  std::chrono::steady_clock::time_point t;
  auto last_time = std::chrono::steady_clock::now();
  int frame_count = 0;

  while (!exiter.exit()) {
    camera.read(img, t);
    frame_count++;
    auto now = std::chrono::steady_clock::now();
    if (std::chrono::duration<double>(now - last_time).count() >= 1.0) {
      double fps = frame_count / std::chrono::duration<double>(now - last_time).count();
      // fmt::print("FPS: {:.2f}\n", fps);
      frame_count = 0;
      last_time = now;
    }

    auto q = gimbal.q(t);
    auto ypr = tools::eulers(q, 2, 1, 0);
    auto gs = gimbal.state();

    recorder.record(img, q, t);

    solver.set_R_gimbal2world(q);
    auto armors = yolo.detect(img);
    auto targets = tracker.track(armors, t);

    PlannerInput planner_input;
    planner_input.target = targets.empty() ? std::nullopt : std::optional<auto_aim::Target>(targets.front());
    planner_input.bullet_speed = gs.bullet_speed;
    planner_input.yaw = ypr[0];
    planner_input.pitch = ypr[1];
    planner_input.t = t;
    target_queue.push(planner_input);
    auto key = cv::waitKey(1);
    if (key == 'q') break;
  }

  quit = true;
  PlannerInput dummy;
  dummy.target = std::nullopt;
  dummy.bullet_speed = 22.0;
  dummy.yaw = 0.0;
  dummy.pitch = 0.0;
  dummy.t = std::chrono::steady_clock::now();
  target_queue.push(dummy);
  if (plan_thread.joinable()) plan_thread.join();
  gimbal.send(false, false, 0, 0, 0, 0, 0, 0);

  return 0;
}