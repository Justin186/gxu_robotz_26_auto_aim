#include <fmt/core.h>

#include <atomic>
#include <chrono>
#include <opencv2/opencv.hpp>
#include <thread>

#include "io/ros2/subscribe2sim.hpp"
#include "io/ros2/publish2sim.hpp"
#include "io/sim_imu/sim_imu.hpp"
#include "tasks/auto_aim/planner/planner.hpp"
#include "tasks/auto_aim/solver.hpp"
#include "tasks/auto_aim/tracker.hpp"
#include "tasks/auto_aim/yolo.hpp"
#include "tools/exiter.hpp"
#include "tools/img_tools.hpp"
#include "tools/logger.hpp"
#include "tools/math_tools.hpp"
#include "tools/thread_safe_queue.hpp"

using namespace std::chrono_literals;

const std::string keys =
  "{help h usage ? |                    | 输出命令行参数说明}"
  "{rec            | false               | 是否录制数据}"
  "{@config-path   | configs/sim.yaml   | 位置参数，yaml配置文件路径 }";

int main(int argc, char * argv[])
{
  tools::Exiter exiter;

  cv::CommandLineParser cli(argc, argv, keys);
  auto config_path = cli.get<std::string>(0);
  auto record = cli.get<bool>("rec");
  if (cli.has("help") || config_path.empty()) {
    cli.printMessage();
    return 0;
  }

  // ===== 初始化 ROS2 =====
  rclcpp::init(argc, argv);
  
  // ===== 创建唯一的节点 =====
  auto node = std::make_shared<rclcpp::Node>("auto_aim_sim_node");
  
  // ===== 创建各模块（共享同一个节点） =====
  io::SimIMU sim_imu(node, config_path);
  io::subscribe2sim image_subscriber(node, config_path);
  io::publish2sim cmd_publisher(node, config_path);

  // ===== 算法模块 =====
  auto_aim::YOLO yolo(config_path, true);
  auto_aim::Solver solver(config_path);
  auto_aim::Tracker tracker(config_path, solver);
  auto_aim::Planner planner(config_path);

  // ===== 目标队列 =====
  tools::ThreadSafeQueue<std::optional<auto_aim::Target>, true> target_queue(1);
  target_queue.push(std::nullopt);

  // ===== 规划线程 =====
  std::atomic<bool> quit = false;
  auto plan_thread = std::thread([&]() {
    while (!quit) {
      auto target = target_queue.front();
      auto gs = sim_imu.state();
      auto plan = planner.plan(
        target, 
        gs.bullet_speed, 
        gs.yaw, 
        gs.pitch, 
        gs.yaw_offset, 
        gs.pitch_offset
      );

      cmd_publisher.send_gimbal_cmd(
        plan.v_pitch * 57.3,
        plan.v_yaw * 57.3,
        0.0,
        0.0,
        5.0,
        plan.fire
      );

      std::this_thread::sleep_for(10ms);
    }
  });

  // ===== 主循环 =====
  cv::Mat img;
  cv::Mat display_img;
  std::chrono::steady_clock::time_point t;
  auto last_t = std::chrono::steady_clock::now();

  // 使用单独的线程处理 ROS 回调
  std::thread spin_thread([&]() {
    rclcpp::spin(node);
  });

  while (!exiter.exit()) {
    // 获取图像
    image_subscriber.read(img, t);
    
    auto now = std::chrono::steady_clock::now();
    double fps = 1.0 / std::chrono::duration<double>(now - last_t).count();
    last_t = now;

    // 获取云台姿态
    auto q = sim_imu.q(t);

    // 算法处理（使用原图）
    solver.set_R_gimbal2world(q);
    auto armors = yolo.detect(img);
    auto targets = tracker.track(armors, t);
    
    if (!targets.empty())
      target_queue.push(targets.front());
    else
      target_queue.push(std::nullopt);

    // ===== 创建显示副本 =====
    display_img = img.clone();

    // 在显示副本上绘制
    if (!targets.empty()) {
      auto target = targets.front();

      // 绘制装甲板
      std::vector<Eigen::Vector4d> armor_xyza_list = target.armor_xyza_list();
      for (const Eigen::Vector4d & xyza : armor_xyza_list) {
        auto image_points =
          solver.reproject_armor(xyza.head(3), xyza[3], target.armor_type, target.name);
        tools::draw_points(display_img, image_points, {0, 255, 0});
      }

      // 绘制瞄准点
      Eigen::Vector4d aim_xyza = planner.debug_xyza();
      auto image_points =
        solver.reproject_armor(aim_xyza.head(3), aim_xyza[3], target.armor_type, target.name);
      tools::draw_points(display_img, image_points, {0, 0, 255});
    }

    // 绘制 FPS（黄色，在左上角）
    tools::draw_text(display_img, fmt::format("FPS: {:.1f}", fps), {10, 30}, {0, 255, 255});
    
    // 显示
    cv::resize(display_img, display_img, {}, 0.5, 0.5);
    cv::imshow("reprojection", display_img);
    
    auto key = cv::waitKey(1);
    if (key == 'q') break;
  }

  // ===== 清理 =====
  quit = true;
  if (plan_thread.joinable()) plan_thread.join();
  
  // 发送停止指令
  cmd_publisher.send_gimbal_cmd(0.0, 0.0, 0.0, 0.0, 0.0, false);
  
  // 停止 ROS
  rclcpp::shutdown();
  if (spin_thread.joinable()) spin_thread.join();

  return 0;
}