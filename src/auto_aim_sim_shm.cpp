#include <fmt/core.h>

#include <atomic>
#include <chrono>
#include <opencv2/opencv.hpp>
#include <thread>

#include "io/shm_ipc/shm_adapter.hpp"
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

using namespace std::chrono_literals;

const std::string keys =
  "{help h usage ? |                    | 输出命令行参数说明}"
  "{rec            | false               | 是否录制数据}"
  "{@config-path   | configs/sim.yaml   | 位置参数，yaml配置文件路径 }";

int main(int argc, char * argv[])
{
  tools::Exiter exiter;
  tools::Recorder recorder;

  cv::CommandLineParser cli(argc, argv, keys);
  auto config_path = cli.get<std::string>(0);
  auto record = cli.get<bool>("rec");
  if (cli.has("help") || config_path.empty()) {
    cli.printMessage();
    return 0;
  }

  // ===== 连接共享内存 =====
  io::ShmAdapter shm;
  if (!shm.is_connected()) {
    std::cerr << "[Error] Failed to connect to shared memory!" << std::endl;
    return 1;
  }
  shm.print_status();

  // ===== 算法模块 =====
  auto_aim::YOLO yolo(config_path, false);
  auto_aim::Solver solver(config_path);
  auto_aim::Tracker tracker(config_path, solver);
  auto_aim::Planner planner(config_path);

  // ===== 目标队列 =====
  tools::ThreadSafeQueue<std::optional<auto_aim::Target>, true> target_queue(1);
  target_queue.push(std::nullopt);

  // ===== 规划线程 =====
  std::atomic<bool> quit = false;
  
  // 用于在图像上显示的指令信息
  struct CmdInfo {
    float yaw_deg = 0.0f;
    float pitch_deg = 0.0f;
    bool fire = false;
    bool has_target = false;
  };
  CmdInfo last_cmd_info;

  auto plan_thread = std::thread([&]() {
    while (!quit) {
      auto target = target_queue.front();
      
      // 从共享内存读取云台状态
      io::SimIMUState gs = shm.state();
      
      auto plan = planner.plan(
        target, 
        gs.bullet_speed, 
        gs.yaw, 
        gs.pitch, 
        gs.yaw_offset, 
        gs.pitch_offset
      );

      // 计算指令值（度）
      float cmd_yaw = plan.v_yaw * 57.3;
      float cmd_pitch = -plan.v_pitch * 57.3;

      // 保存指令信息用于显示
      last_cmd_info.yaw_deg = cmd_yaw;
      last_cmd_info.pitch_deg = cmd_pitch;
      last_cmd_info.fire = plan.fire;
      last_cmd_info.has_target = target.has_value();

      // 发送云台指令
      shm.send_gimbal_cmd(
        cmd_yaw,                    // yaw (度)
        cmd_pitch,                  // pitch (度)
        5.0,                        // distance (米)
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
  double fps_smooth = 0.0;
  const double alpha = 0.1;

  while (!exiter.exit()) {
    // 1. 读取图像并从共享内存消费一整轮话题集。
    //    新版 sim 采用"图像 + 四位姿"捆绑式同步发布：唯有把上一轮的五路全部消费完毕，
    //    它才会放出下一帧。consume_next_frame() 已在取图之余代劳消费其余位姿通道，
    //    避免了因残留 dirty 标志而导致 sim 拒发新帧、窗口迟迟不出现的"伪卡死"。
    if (!shm.consume_next_frame(img, t)) {
      std::this_thread::sleep_for(1ms);
      continue;
    }
    
    // 2. 计算 FPS（平滑）
    auto now = std::chrono::steady_clock::now();
    double fps_instant = 1.0 / std::chrono::duration<double>(now - last_t).count();
    fps_smooth = alpha * fps_instant + (1.0 - alpha) * fps_smooth;
    last_t = now;

    // 3. 读取云台姿态（四元数）
    Eigen::Quaterniond q;
    uint64_t timestamp_ns;
    if (!shm.read_gimbal_pose(q, timestamp_ns)) {
      continue;
    }

    // 4. 算法处理
    solver.set_R_gimbal2world(q);
    auto armors = yolo.detect(img);
    auto targets = tracker.track(armors, t);
    
    if (!targets.empty())
      target_queue.push(targets.front());
    else
      target_queue.push(std::nullopt);

    // 5. 录制数据（可选）
    if (record) {
      recorder.record(img, q, t);
    }

    // ===== 绘制显示 =====
    display_img = img.clone();

    // 绘制装甲板和瞄准点
    if (!targets.empty()) {
      auto target = targets.front();

      std::vector<Eigen::Vector4d> armor_xyza_list = target.armor_xyza_list();
      for (const Eigen::Vector4d & xyza : armor_xyza_list) {
        auto image_points =
          solver.reproject_armor(xyza.head(3), xyza[3], target.armor_type, target.name);
        tools::draw_points(display_img, image_points, {0, 255, 0});
      }

      Eigen::Vector4d aim_xyza = planner.debug_xyza();
      auto image_points =
        solver.reproject_armor(aim_xyza.head(3), aim_xyza[3], target.armor_type, target.name);
      tools::draw_points(display_img, image_points, {0, 0, 255});
    }

    // ===== 绘制 FPS =====
    tools::draw_text(display_img, fmt::format("FPS: {:.1f}", fps_smooth), {10, 30}, {0, 255, 255});

    // ===== 绘制云台指令信息 =====
    int line_y = 70;
    tools::draw_text(display_img, 
      fmt::format("Target: {}", last_cmd_info.has_target ? "YES" : "NO"), 
      {10, line_y}, 
      last_cmd_info.has_target ? cv::Scalar(0, 255, 0) : cv::Scalar(0, 0, 255));
    
    line_y += 40;
    tools::draw_text(display_img, 
      fmt::format("Cmd Yaw: {:.2f} deg", last_cmd_info.yaw_deg), 
      {10, line_y}, {255, 255, 0});
    
    line_y += 40;
    tools::draw_text(display_img, 
      fmt::format("Cmd Pitch: {:.2f} deg", last_cmd_info.pitch_deg), 
      {10, line_y}, {255, 255, 0});
    
    line_y += 40;
    tools::draw_text(display_img, 
      fmt::format("Fire: {}", last_cmd_info.fire ? "ON" : "OFF"), 
      {10, line_y}, 
      last_cmd_info.fire ? cv::Scalar(0, 0, 255) : cv::Scalar(128, 128, 128));

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
  shm.send_gimbal_cmd(0.0, 0.0, 0.0, false);

  std::cout << "[AutoAim] Shutting down..." << std::endl;

  return 0;
}