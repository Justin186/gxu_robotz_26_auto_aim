#include <fmt/core.h>

#include <atomic>
#include <chrono>
#include <deque>
#include <nlohmann/json.hpp>
#include <opencv2/opencv.hpp>
#include <thread>
// #include <rerun.hpp>

#include "io/camera.hpp"
#include "io/ros2/gimbal_node.hpp"
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

using namespace std::chrono_literals;

const std::string keys =
  "{help h usage ? |                        | 输出命令行参数说明}"
  "{ip             | 100.81.72.108          | Rerun 查看器的IP地址}"
  "{@config-path   | configs/sentry.yaml    | 位置参数，yaml配置文件路径 }";

int main(int argc, char * argv[])
{
  tools::Exiter exiter;
  tools::Plotter plotter; // 启用 Plotter

  cv::CommandLineParser cli(argc, argv, keys);
  auto config_path = cli.get<std::string>(0);
  auto rerun_ip = cli.get<std::string>("ip");

  if (cli.has("help") || config_path.empty()) {
    cli.printMessage();
    return 0;
  }

  // const auto rec = rerun::RecordingStream("gxu_auto_aim_debug");
  // // 连接到调试机的 IP 地址
  // rec.connect_grpc("rerun+http://" + rerun_ip + ":9876/proxy").exit_on_failure();

  io::GimbalNode gimbal(config_path);
  io::Camera camera(config_path);

  auto_aim::YOLO yolo(config_path, true);
  auto_aim::Solver solver(config_path);
  auto_aim::Tracker tracker(config_path, solver);
  auto_aim::Planner planner(config_path);

  auto yaml = tools::load(config_path);
  auto R_gimbal2imubody_data = tools::read<std::vector<double>>(yaml, "R_gimbal2imubody");
  Eigen::Matrix<double, 3, 3, Eigen::RowMajor> R_gimbal2imubody(R_gimbal2imubody_data.data());
  auto fire_duty_window = tools::read<size_t>(yaml, "fire_duty_window", 500);

  tools::ThreadSafeQueue<std::optional<auto_aim::Target>, true> target_queue(1);
  target_queue.push(std::nullopt);

  std::atomic<bool> quit = false;
  auto plan_thread = std::thread([&]() {
    auto t0 = std::chrono::steady_clock::now();
    uint16_t last_bullet_count = 0;

    std::deque<bool> fire_history;
    const size_t history_max_size = fire_duty_window;

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

      // =========================================================================
      // [通用部分] 无论是否有目标，始终更新 Rerun 中的云台 3D 姿态（让扫描时云台也能动）
      // =========================================================================
      auto q_gimbal = gimbal.q(current_time); 
      Eigen::Matrix3d R_imubody2world = q_gimbal.toRotationMatrix();
      Eigen::Matrix3d R_gimbal2world = R_imubody2world * R_gimbal2imubody;
      
      // 绘制云台坐标轴
      // rec.log("world/gimbal", 
      //   rerun::Transform3D(
      //     rerun::Vec3D{0.0f, 0.0f, 0.0f},
      //     rerun::Mat3x3({ 
      //       (float)R_gimbal2world(0,0), (float)R_gimbal2world(1,0), (float)R_gimbal2world(2,0),
      //       (float)R_gimbal2world(0,1), (float)R_gimbal2world(1,1), (float)R_gimbal2world(2,1),
      //       (float)R_gimbal2world(0,2), (float)R_gimbal2world(1,2), (float)R_gimbal2world(2,2)
      //     })
      //   ),
      //   rerun::TransformAxes3D(0.5) 
      // );
      
      // 提取云台正前方，投影到水平面作为辅助线
      Eigen::Vector3d forward_world = R_gimbal2world.col(0); 
      forward_world.z() = 0.0; 
      if (forward_world.norm() > 1e-6) forward_world.normalize();
      else forward_world = Eigen::Vector3d(1.0, 0.0, 0.0);

      Eigen::Vector3d local_dir = R_gimbal2world.transpose() * forward_world;
      Eigen::Vector3d world_offset(0.0, 0.0, -0.27);
      Eigen::Vector3d local_offset = R_gimbal2world.transpose() * world_offset;

      // std::vector<rerun::components::LineStrip3D> strips;
      // strips.push_back(rerun::components::LineStrip3D({
      //   {(float)local_offset.x(), (float)local_offset.y(), (float)local_offset.z()}, 
      //   {(float)(local_offset.x() + 8.0 * local_dir.x()), 
      //    (float)(local_offset.y() + 8.0 * local_dir.y()), 
      //    (float)(local_offset.z() + 8.0 * local_dir.z())}
      // }));

      // rec.log("world/gimbal/yaw_line", rerun::LineStrips3D(strips).with_colors({{255, 165, 0}}));


      // =========================================================================
      // [分支控制] 根据是否有目标执行不同逻辑
      // =========================================================================
      if (target.has_value()) {
        first_scan = true; // 发现目标后，下次扫描从新位置开始
        // --- 1. 发现目标：预测与控制 ---
        auto plan = planner.plan(target, gs.bullet_speed);
        gimbal.set_aim_status(true);

        gimbal.send(
          plan.control, plan.fire, plan.yaw, plan.yaw_vel, plan.yaw_acc, 
          -plan.pitch, -plan.pitch_vel, -plan.pitch_acc);

        auto fired = gs.bullet_count > last_bullet_count;
        last_bullet_count = gs.bullet_count;

        // --- 2. 准备发给 Plotter 的 JSON 数据 ---
        nlohmann::json data;
        data["t"] = tools::delta_time(current_time, t0);

        data["gimbal_yaw"] = gs.yaw / 57.3;
        data["gimbal_yaw_vel"] = gs.yaw_vel;
        data["gimbal_pitch"] = gs.pitch / 57.3;
        data["gimbal_pitch_vel"] = gs.pitch_vel;
        data["bullet_speed"] = gs.bullet_speed;

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
        data["is_scan"] = 0;

        data["target_z"] = target->ekf_x()[4];   //z
        data["target_vz"] = target->ekf_x()[5];  //vz
        data["w"] = target->ekf_x()[7];          //w

        plotter.plot(data);

        // --- 3. 发送给 Rerun 的标量曲线 ---
        // rec.log("yaw/plan_yaw", rerun::Scalars(plan.yaw));
        // rec.log("yaw/target_yaw", rerun::Scalars(plan.target_yaw));
        // rec.log("yaw/gimbal_yaw", rerun::Scalars(gs.yaw));
        // rec.log("yaw/gimbal_yaw_vel", rerun::Scalars(gs.yaw_vel));
        // rec.log("yaw/plan_yaw_vel", rerun::Scalars(plan.yaw_vel));
        // rec.log("yaw/plan_yaw_acc", rerun::Scalars(plan.yaw_acc));
        
        // rec.log("pitch/plan_pitch", rerun::Scalars(plan.pitch));
        // rec.log("pitch/target_pitch", rerun::Scalars(plan.target_pitch));
        // rec.log("pitch/gimbal_pitch", rerun::Scalars(gs.pitch));
        // rec.log("pitch/plan_pitch_vel", rerun::Scalars(plan.pitch_vel));
        // rec.log("pitch/plan_pitch_acc", rerun::Scalars(plan.pitch_acc));

        // rec.log("scalar/target/z", rerun::Scalars(target->ekf_x()[4]));
        // rec.log("scalar/target/vz", rerun::Scalars(target->ekf_x()[5]));
        // rec.log("scalar/target/w", rerun::Scalars(target->ekf_x()[7]));

        // --- 4. 开火占空比计算 ---
        fire_history.push_back(plan.fire);
        if (fire_history.size() > history_max_size) {
          fire_history.pop_front();
        }
        double fire_duty = 0.0;
        for (bool f : fire_history) {
          if (f) fire_duty += 1.0;
        }
        fire_duty /= fire_history.size();

        // rec.log("fire/plan_fire", rerun::Scalars(plan.fire ? 1.0f : 0.0f));
        // rec.log("fire/duty_cycle", rerun::Scalars(fire_duty));

        // --- 5. Rerun 3D 装甲板与预测点可视化 ---
        // std::vector<rerun::Position3D> armor_points;
        // for (const auto& xyza : target->armor_xyza_list()) {
        //   armor_points.push_back({(float)xyza[0], (float)xyza[1], (float)xyza[2]});
        // }
        
        // Eigen::Vector4d aim_xyza = planner.debug_xyza;
        // std::vector<rerun::Position3D> aim_points = {
        //   {(float)aim_xyza[0], (float)aim_xyza[1], (float)aim_xyza[2]}
        // };
        
        // rec.log("world/target/armors", rerun::Points3D(armor_points)
        //   .with_radii({0.05f}).with_colors({{0, 255, 0}})); 
        
        // rec.log("world/target/aim_point", rerun::Points3D(aim_points)
        //   .with_radii({0.07f}).with_colors({{255, 0, 0}})); 

        std::this_thread::sleep_for(10ms);

      } else { 
        gimbal.set_aim_status(false);
        // --- 丢失目标时：执行扫描 ---
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
        
        // 发送给 Plotter
        nlohmann::json data;
        data["gimbal_yaw"] = gs.yaw / 57.3;
        data["gimbal_pitch"] = gs.pitch / 57.3;
        data["plan_yaw"] = yaw;
        data["plan_pitch"] = pitch;
        data["t"] = tools::delta_time(current_time, t0);
        data["is_scan"] = 1;
        data["bullet_speed"] = gs.bullet_speed;
        data["current_hp"] = gs.current_hp;

        plotter.plot(data);

        // 清空 Rerun 中的小球，防止屏幕留着鬼影
        // rec.log("world/target/armors", rerun::Clear::FLAT);
        // rec.log("world/target/aim_point", rerun::Clear::FLAT);

        std::this_thread::sleep_for(10ms);
      }
    }
  });

  cv::Mat img;
  std::chrono::steady_clock::time_point t;
  auto last_t = std::chrono::steady_clock::now();

  while (!exiter.exit()) {
    camera.read(img, t);
    auto now = std::chrono::steady_clock::now();
    double fps = 1.0 / std::chrono::duration<double>(now - last_t).count();
    last_t = now;
    
    auto q = gimbal.q(t);

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

    tools::draw_text(img, fmt::format("FPS: {:.2f}", fps), {10, 30});
    cv::resize(img, img, {}, 0.7, 0.7);  // 显示时缩小图片尺寸
    cv::imshow("reprojection", img);
    auto key = cv::waitKey(1);
    if (key == 'q') break;
  }

  quit = true;
  if (plan_thread.joinable()) plan_thread.join();
  gimbal.send(false, false, 0, 0, 0, 0, 0, 0);

  return 0;
}