#include <fmt/core.h>

#include <atomic>
#include <chrono>
#include <nlohmann/json.hpp>
#include <opencv2/opencv.hpp>
#include <thread>

#include "io/camera.hpp"
#include "io/gimbal/gimbal.hpp"
#include "io/ros2/gimbal_node.hpp"
#include "tasks/auto_aim/planner/planner.hpp"
#include "tasks/auto_aim/solver.hpp"
#include "tasks/auto_aim/tracker.hpp"
#include "tasks/auto_aim/yolo.hpp"
#include "tools/exiter.hpp"
#include "tools/img_tools.hpp"
#include "tools/logger.hpp"
#include "tools/math_tools.hpp"
#include "tools/thread_safe_queue.hpp"
#include "tools/recorder.hpp"
// 移除了 Plotter 头文件依赖，如果在其他地方没用到

using namespace std::chrono_literals;

const std::string keys =
  "{help h usage ? |                        | 输出命令行参数说明}"
  "{@config-path   | configs/sentry.yaml | 位置参数，yaml配置文件路径 }";

int main(int argc, char * argv[])
{
  tools::Exiter exiter;
  tools::Recorder recorder(30);
  // 删除 Plotter，部署版本不需要画图表

  // 1. 修复：必须先声明 cli 解析器
  cv::CommandLineParser cli(argc, argv, keys);
  auto config_path = cli.get<std::string>(0);
  if (cli.has("help") || config_path.empty()) {
    cli.printMessage();
    return 0;
  }

  io::GimbalNode gimbal(config_path);
  io::Camera camera(config_path); 

  // 第二个参数 false 关闭 YOLO 调试窗口
  auto_aim::YOLO yolo(config_path, false); 
  auto_aim::Solver solver(config_path);
  auto_aim::Tracker tracker(config_path, solver);
  auto_aim::Planner planner(config_path);

  tools::ThreadSafeQueue<std::optional<auto_aim::Target>, true> target_queue(1);
  target_queue.push(std::nullopt);

  std::atomic<bool> quit = false;
  auto plan_thread = std::thread([&]() {
    // 部署版本移除了 debug 统计用的计时器和 bullet_count 逻辑，只保留核心控制
    // 如果需要统计射击，可以加回来，但不做 Plotter 绘图

    auto last_scan_time = std::chrono::steady_clock::now();
    double scan_cmd_angle = 0.0;
    double scan_t = 0.0;
    bool first_scan = true;

    while (!quit) {
      auto target = target_queue.front();
      auto gs = gimbal.state();
      auto current_time = std::chrono::steady_clock::now();
      double dt = tools::delta_time(current_time, last_scan_time);
      last_scan_time = current_time;

      if (tracker.state() != "lost") { 
        first_scan = true;
        auto plan = planner.plan(target, gs.bullet_speed);
        gimbal.set_aim_status(true);

        gimbal.send(
          plan.control, plan.fire, 
          plan.yaw, plan.yaw_vel, plan.yaw_acc, 
          -plan.pitch, -plan.pitch_vel, -plan.pitch_acc);

        std::this_thread::sleep_for(10ms);
      } 
      else if (tracker.state() == "lost" && !io::GimbalNode::is_move)
      { 
        gimbal.set_aim_status(false);
        
        if (first_scan) {
          scan_cmd_angle = gs.yaw * 57.3; // 以当前实际yaw为起点
          first_scan = false;
        }

        double delta_angle = 30.0; // 哨兵扫描：yaw 每秒旋转度数
        double amplitude = 15.0;   // 哨兵扫描：pitch 上下扫动幅度(度)
        double period = 2.0;       // 哨兵扫描：pitch 扫动周期(秒)

        scan_cmd_angle += delta_angle * dt;
        double yaw = tools::limit_rad(scan_cmd_angle / 57.3);
        double pitch = tools::limit_rad(amplitude * std::sin(2 * M_PI * scan_t / period) / 57.3);
        
        gimbal.send(true, false, yaw, 0, 0, pitch, 0, 0);

        scan_t += dt;
        if (scan_t >= period) {
            scan_t -= period;
        }

        std::this_thread::sleep_for(10ms);
      }
      else {
        // 增加一个 else 分支，防止既没目标又在移动时死循环空转占用 CPU
        std::this_thread::sleep_for(10ms);
      }
    }
  });

  cv::Mat img;
  std::chrono::steady_clock::time_point t;

  while (!exiter.exit()) {
    camera.read(img, t); // 相机读取通常是阻塞的，控制了整体循环频率
    auto q = gimbal.q(t);
    // 比赛进行中则开始录制
    if (gimbal.nav_state().game_progress == 1) { // 1: 准备阶段, 4: 比赛进行中 (需确认game_progress对应的值, 根据不同赛季可能不同, 这里用户只要求是1)
        recorder.record(img, q, t);
    }

    
    solver.set_R_gimbal2world(q);
    auto armors = yolo.detect(img);
    auto targets = tracker.track(armors, t);
    if (!targets.empty())
      target_queue.push(targets.front());
    else
      target_queue.push(std::nullopt);

    if (!targets.empty()) {
      auto target = targets.front();

      // 当前帧target更新后
      std::vector<Eigen::Vector4d> armor_xyza_list = target.armor_xyza_list();
      for (const Eigen::Vector4d & xyza : armor_xyza_list) {
        auto image_points =
          solver.reproject_armor(xyza.head(3), xyza[3], target.armor_type, target.name);
        tools::draw_points(img, image_points, {0, 255, 0});
      }

      Eigen::Vector4d aim_xyza = planner.debug_xyza;
      auto image_points =
        solver.reproject_armor(aim_xyza.head(3), aim_xyza[3], target.armor_type, target.name);
      tools::draw_points(img, image_points, {0, 0, 255});
    }

    // cv::resize(img, img, {}, 0.5, 0.5);  // 显示时缩小图片尺寸
    // cv::imshow("reprojection", img);
    auto key = cv::waitKey(1);
    if (key == 'q') break;
  }

  quit = true;
  if (plan_thread.joinable()) plan_thread.join();
  gimbal.send(false, false, 0, 0, 0, 0, 0, 0);

  return 0;
}