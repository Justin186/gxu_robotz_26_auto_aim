#include <fmt/core.h>

#include <atomic>
#include <chrono>
#include <deque>
#include <nlohmann/json.hpp>
#include <opencv2/opencv.hpp>
#include <thread>
#include <rerun.hpp>

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

using namespace std::chrono_literals;

const std::string keys =
  "{help h usage ? |                        | 输出命令行参数说明}"
  "{ip             | 192.168.1.18           | Rerun 查看器的IP地址}"
  "{f              | true                   | 是否开火}"
  "{debug          | false                  | 是否显示图像调试窗口}"
  "{@config-path   | configs/sentry.yaml    | 位置参数，yaml配置文件路径 }";

int main(int argc, char * argv[])
{
  tools::Exiter exiter;
  // tools::Plotter plotter;

  cv::CommandLineParser cli(argc, argv, keys);
  auto config_path = cli.get<std::string>(0);
  auto rerun_ip = cli.get<std::string>("ip");
  auto fire = cli.get<bool>("f");
  auto debug = cli.get<bool>("debug");
  if (cli.has("help") || config_path.empty()) {
    cli.printMessage();
    return 0;
  }

  const auto rec = rerun::RecordingStream("gxu_auto_aim_debug");
  // 连接到你场下大电脑(调试机)的 IP 地址
  rec.connect_grpc("rerun+http://" + rerun_ip + ":9876/proxy").exit_on_failure();

  io::Gimbal gimbal(config_path);
  io::Camera camera(config_path);

  auto_aim::YOLO yolo(config_path, debug);
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

      // 实时记录一下yaw和pitch的角度，让它们在Rerun上产生时间序列图表，类似PlotJuggler
      auto current_time = std::chrono::steady_clock::now();
      // rec.set_time_duration_secs("plots_time", tools::delta_time(current_time, t0));
      
      auto q_gimbal = gimbal.q(current_time); // 必须使用当前时间去获取四元数
      Eigen::Matrix3d R_imubody2world = q_gimbal.toRotationMatrix();
      
      Eigen::Matrix3d R_gimbal2world = R_imubody2world * R_gimbal2imubody;
      
      // 以云台中心作为原点，绘制云台当前坐标系。利用 TransformAxes3D 能够画出红绿蓝(XYZ)三个箭头的坐标轴
      rec.log("world/gimbal", 
        rerun::Transform3D(
          rerun::Vec3D{0.0f, 0.0f, 0.0f}, // 云台坐标系原点在世界坐标系中的位置（我们这里假设云台安装在机器人正中心，所以就是全局原点）
          rerun::Mat3x3({ // Rerun的Mat3x3为【列主序】(Column-Major)！必须修成这样，否则矩阵就是转置的，会导致所有旋转颠倒。
            (float)R_gimbal2world(0,0), (float)R_gimbal2world(1,0), (float)R_gimbal2world(2,0),
            (float)R_gimbal2world(0,1), (float)R_gimbal2world(1,1), (float)R_gimbal2world(2,1),
            (float)R_gimbal2world(0,2), (float)R_gimbal2world(1,2), (float)R_gimbal2world(2,2)
          })
        ),
        rerun::TransformAxes3D(0.5) // 参数0.5代表这三根红色、绿色、蓝色轴的可视化长度为 0.5 米
      );
      
      // 我们从已经修正好的真实的 IMU 旋转矩阵里，提取出云台当前的真实世界前方(X轴)，并强行拍平在水平面上。
      Eigen::Vector3d forward_world = R_gimbal2world.col(0); 
      forward_world.z() = 0.0; // 强制砍掉所有的 Z 轴数值，让它在全局地图里绝对处于绝对水平！
      if (forward_world.norm() > 1e-6) forward_world.normalize();
      else forward_world = Eigen::Vector3d(1.0, 0.0, 0.0);

      // 为了把这根线绑定在 gimbal 的子层级下（使得线段起点跟随云台），我们需要将世界纯水平指向反向变换回 gimbal 局部系中
      Eigen::Vector3d local_dir = R_gimbal2world.transpose() * forward_world;
      
      // 用户要求在全局（世界坐标系）下降 0.27m。我们需要将世界系下的向下向量 (0, 0, -0.27) 也反向变换到 gimbal 局部系里，作为线段的起点偏移
      Eigen::Vector3d world_offset(0.0, 0.0, 0.0);
      Eigen::Vector3d local_offset = R_gimbal2world.transpose() * world_offset;

      std::vector<rerun::components::LineStrip3D> strips;
      strips.push_back(rerun::components::LineStrip3D({
        {(float)local_offset.x(), (float)local_offset.y(), (float)local_offset.z()}, // 起点也带上在世界系里下降的局部偏移
        {(float)(local_offset.x() + 8.0 * local_dir.x()), 
         (float)(local_offset.y() + 8.0 * local_dir.y()), 
         (float)(local_offset.z() + 8.0 * local_dir.z())}
      }));

      // 因为 Rerun 自动对子层应用正向旋转，这正好抵消了我们刚刚乘的逆向转置矩阵（且R_gimbal矩阵已被正确修复），现在肯定完全水平了！
      rec.log("world/gimbal/yaw_line",
        rerun::LineStrips3D(strips).with_colors({{255, 165, 0}}) // 橙色直线
      );

      rec.log("yaw/plan_yaw", rerun::Scalars(plan.yaw));
      rec.log("yaw/target_yaw", rerun::Scalars(plan.target_yaw));
      rec.log("yaw/gimbal_yaw", rerun::Scalars(gs.yaw));
      rec.log("yaw/gimbal_yaw_vel", rerun::Scalars(gs.yaw_vel));
      rec.log("yaw/plan_yaw_vel", rerun::Scalars(plan.yaw_vel));
      rec.log("yaw/plan_yaw_acc", rerun::Scalars(plan.yaw_acc));
      

      rec.log("pitch/plan_pitch", rerun::Scalars(plan.pitch));
      rec.log("pitch/target_pitch", rerun::Scalars(plan.target_pitch));
      rec.log("pitch/gimbal_pitch", rerun::Scalars(gs.pitch));
      rec.log("pitch/plan_pitch_vel", rerun::Scalars(plan.pitch_vel));
      rec.log("pitch/plan_pitch_acc", rerun::Scalars(plan.pitch_acc));

      fire_history.push_back(plan.fire);
      if (fire_history.size() > history_max_size) {
        fire_history.pop_front();
      }
      double fire_duty = 0.0;
      for (bool f : fire_history) {
        if (f) fire_duty += 1.0;
      }
      fire_duty /= fire_history.size();

      rec.log("fire/plan_fire", rerun::Scalars(plan.fire ? 1.0f : 0.0f));
      rec.log("fire/duty_cycle", rerun::Scalars(fire_duty));

      // gs.bullet_speed
      rec.log("scalar/bullet_speed", rerun::Scalars(gs.bullet_speed));

      // 记录目标位置 (如果有)
      if (target.has_value()) {
        std::vector<rerun::Position3D> armor_points;
        auto armor_xyza_list = target->armor_xyza_list();
        for (const auto& xyza : armor_xyza_list) {
          // X, Y, Z
          armor_points.push_back({(float)xyza[0], (float)xyza[1], (float)xyza[2]});
        }
        
        // 可视化预测击打点 (从 planner 获取)
        Eigen::Vector4d aim_xyza = planner.debug_xyza;
        std::vector<rerun::Position3D> aim_points = {
          {(float)aim_xyza[0], (float)aim_xyza[1], (float)aim_xyza[2]}
        };
        
        // 用一个绿色小球表示各个正在估计的装甲板空间位置
        rec.log("world/target/armors", rerun::Points3D(armor_points)
          .with_radii({0.05f})
          .with_colors({{0, 255, 0}})); // 绿色代表当前装甲板
        
        // 用一个比较大的红色小球表示要打的点
        rec.log("world/target/aim_point", rerun::Points3D(aim_points)
          .with_radii({0.07f})
          .with_colors({{255, 0, 0}})); // 红色代表预测击打位置
          
        rec.log("scalar/target/w", rerun::Scalars(target->ekf_x()[7])); // 记录目标的旋转角速度w
        rec.log("scalar/target/z", rerun::Scalars(target->ekf_x()[4]));
        rec.log("scalar/target/vz", rerun::Scalars(target->ekf_x()[5]));
        rec.log("scalar/target/r", rerun::Scalars(target->ekf_x()[8]));
      } else {
        // 丢失目标时清空绘制，防止屏幕上留着鬼影
        rec.log("world/target/armors", rerun::Clear::FLAT);
        rec.log("world/target/aim_point", rerun::Clear::FLAT);
      }
      // =========================
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
    cv::resize(img, img, {}, 0.5, 0.5);  // 显示时缩小图片尺寸
    if (debug) {
      cv::imshow("reprojection", img);
    }
    // 记录图像到 Rerun
    // rec.log("camera/image", rerun::Image(img.data, {(uint32_t)img.cols, (uint32_t)img.rows}, rerun::datatypes::ColorModel::BGR));
    rec.log("scalar/fps", rerun::Scalars((float)fps));
    auto key = cv::waitKey(1);
    if (key == 'q') break;
  }

  quit = true;
  if (plan_thread.joinable()) plan_thread.join();
  gimbal.send(false, false, 0, 0, 0, 0, 0, 0);

  return 0;
}