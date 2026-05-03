#include <fmt/core.h>

#include <atomic>
#include <chrono>
#include <deque>
#include <mutex>
#include <nlohmann/json.hpp>
#include <opencv2/opencv.hpp>
#include <thread>
#include <rerun.hpp>

#include "io/camera.hpp"
#include "io/gimbal/gimbal.hpp"
#include "tasks/video_encoder/video_encoder.hpp"
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
  "{imshow         | true                   | 是否显示图像窗口}"
  "{rerun          | false                  | 是否将数据记录到Rerun}"
  "{camera         | configs/camera.yaml      | 位置参数，yaml配置文件路径 }"
  "{@config-path   | configs/hero.yaml      | 位置参数，yaml配置文件路径 }";

int main(int argc, char * argv[])
{
  tools::Exiter exiter;
  // tools::Plotter plotter;

  cv::CommandLineParser cli(argc, argv, keys);
  auto config_path = cli.get<std::string>(0);
  auto camera_config_path = cli.get<std::string>("camera");
  auto rerun_ip = cli.get<std::string>("ip");
  auto fire = cli.get<bool>("f");
  auto imshow = cli.get<bool>("imshow");
  auto rerun = cli.get<bool>("rerun");

  if (cli.has("help") || config_path.empty()) {
    cli.printMessage();
    return 0;
  }

  std::optional<rerun::RecordingStream> rec; 
  if (rerun) {
    rec.emplace("gxu_auto_aim_debug");
    rec->connect_grpc("rerun+http://" + rerun_ip + ":9876/proxy").exit_on_failure();
  }
  // 连接到你场下大电脑(调试机)的 IP 地址
    // rec.connect_grpc("rerun+http://" + rerun_ip + ":9876/proxy").exit_on_failure();

  io::Gimbal gimbal(config_path);
  io::Camera camera(config_path);
  io::Camera lob_camera(camera_config_path);

  auto_aim::YOLO yolo(config_path, imshow);
  auto_aim::Solver solver(config_path);
  auto_aim::Tracker tracker(config_path, solver);
  auto_aim::Planner planner(config_path);

  auto yaml = tools::load(config_path);
  auto R_gimbal2imubody_data = tools::read<std::vector<double>>(yaml, "R_gimbal2imubody");
  Eigen::Matrix<double, 3, 3, Eigen::RowMajor> R_gimbal2imubody(R_gimbal2imubody_data.data());

  auto fire_duty_window = tools::read<size_t>(yaml, "fire_duty_window", 500);

  tasks::VideoEncoderConfig encoder_config;
  // TODO: 后续如果是双相机，就在 yaml 里读取相应的图传相机配置
  encoder_config.target_bitrate = 80;
  encoder_config.output_fps = 60;       // 利用大带宽重新拉回 60 FPS 流畅度
  
  tasks::VideoEncoder video_encoder(encoder_config, [&](const uint8_t* data, size_t size){
    gimbal.send_video(data, size);

    static int video_send_count = 0;
    static auto last_video_send_time = std::chrono::steady_clock::now();
    video_send_count++;
    auto now = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::seconds>(now - last_video_send_time).count() >= 1) {
      tools::logger()->info("[VideoEncoder] Send frequency: {} Hz", video_send_count);
      video_send_count = 0;
      last_video_send_time = now;
    }
  });

  tools::ThreadSafeQueue<std::optional<auto_aim::Target>, true> target_queue(1);
  target_queue.push(std::nullopt);

  std::atomic<bool> quit = false;
  auto plan_thread = std::thread([&]() {
    auto t0 = std::chrono::steady_clock::now();
    uint16_t last_bullet_count = 0;
    
    std::deque<bool> fire_history;
    const size_t history_max_size = fire_duty_window;
    
    // 用于降低 Rerun 的发送频率 (200Hz -> 50Hz)
    size_t rerun_counter = 0;
    const size_t rerun_interval = 4;

    while (!quit) {
      auto target = target_queue.front();
      auto gs = gimbal.state();
      auto plan = planner.plan(target, gs.bullet_speed, gs.yaw, gs.pitch);
      // auto plan = planner.plan(target, gs.bullet_speed);

      gimbal.send(
        plan.control, plan.fire && fire,
        plan.v_yaw, plan.yaw_vel, plan.yaw_acc,
        plan.v_pitch, plan.pitch_vel, plan.pitch_acc);

      auto fired = gs.bullet_count > last_bullet_count;
      last_bullet_count = gs.bullet_count;

      // 实时记录一下yaw和pitch的角度，让它们在Rerun上产生时间序列图表，类似PlotJuggler
      auto current_time = std::chrono::steady_clock::now();
      
      bool do_rerun = rerun && (rerun_counter % rerun_interval == 0);

      // rec.set_time_duration_secs("plots_time", tools::delta_time(current_time, t0));
      
      auto q_gimbal = gimbal.q(current_time); // 必须使用当前时间去获取四元数
      Eigen::Matrix3d R_imubody2world = q_gimbal.toRotationMatrix();
      
      Eigen::Matrix3d R_gimbal2world = R_imubody2world * R_gimbal2imubody;
      
      // 以云台中心作为原点，绘制云台当前坐标系。利用 TransformAxes3D 能够画出红绿蓝(XYZ)三个箭头的坐标轴
      if (do_rerun) rec->log("world/gimbal", 
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
      if (forward_world.norm() > 1e-6) forward_world.normalize();
      else forward_world = Eigen::Vector3d(1.0, 0.0, 0.0);

      // 为了把这根线绑定在 gimbal 的子层级下（使得线段起点跟随云台），我们需要将世界纯水平指向反向变换回 gimbal 局部系中
      Eigen::Vector3d local_dir = R_gimbal2world.transpose() * forward_world;
      
      Eigen::Vector3d world_offset(0.0, 0.0, 0.0);
      Eigen::Vector3d local_offset = R_gimbal2world.transpose() * world_offset;

      std::vector<rerun::components::LineStrip3D> strips;
      strips.push_back(rerun::components::LineStrip3D({
        {(float)local_offset.x(), (float)local_offset.y(), (float)local_offset.z()}, // 起点也带上在世界系里下降的局部偏移
        {(float)(local_offset.x() + 8.0 * local_dir.x()), 
         (float)(local_offset.y() + 8.0 * local_dir.y()), 
         (float)(local_offset.z() + 8.0 * local_dir.z())}
      }));

      fire_history.push_back(plan.fire);
      if (fire_history.size() > history_max_size) {
        fire_history.pop_front();
      }
      double fire_duty = 0.0;
      for (bool f : fire_history) {
        if (f) fire_duty += 1.0;
      }
      fire_duty /= fire_history.size();

      // 因为 Rerun 自动对子层应用正向旋转，这正好抵消了我们刚刚乘的逆向转置矩阵（且R_gimbal矩阵已被正确修复），现在肯定完全水平了！
      if (do_rerun) { 
        rec->log("world/gimbal/yaw_line",
          rerun::LineStrips3D(strips).with_colors({{255, 165, 0}}) // 橙色直线
        );
        rec->log("yaw/plan_yaw", rerun::Scalars(plan.yaw));
        rec->log("yaw/target_yaw", rerun::Scalars(plan.target_yaw));
        rec->log("yaw/gimbal_yaw", rerun::Scalars(gs.yaw));
        rec->log("yaw/gimbal_yaw_vel", rerun::Scalars(gs.yaw_vel));
        rec->log("yaw/plan_yaw_vel", rerun::Scalars(plan.yaw_vel));
        rec->log("yaw/plan_yaw_acc", rerun::Scalars(plan.yaw_acc));
      

        rec->log("pitch/plan_pitch", rerun::Scalars(plan.pitch));
        rec->log("pitch/target_pitch", rerun::Scalars(plan.target_pitch));
        rec->log("pitch/gimbal_pitch", rerun::Scalars(gs.pitch));
        rec->log("pitch/plan_pitch_vel", rerun::Scalars(plan.pitch_vel));
        rec->log("pitch/plan_pitch_acc", rerun::Scalars(plan.pitch_acc));

        rec->log("fire/fired", rerun::Scalars(fired ? 1.0f : 0.0f));
        rec->log("fire/plan_fire", rerun::Scalars(plan.fire ? 1.0f : 0.0f));
        rec->log("fire/duty_cycle", rerun::Scalars(fire_duty));
      }

      // 记录目标位置 (如果有)
      if (target.has_value()) {
        auto armor_xyza_list = target->armor_xyza_list();
        
        float armor_width = (target->armor_type == auto_aim::ArmorType::big) ? 0.230f : 0.135f;
        float armor_height = 0.056f;
        float pitch = (target->name == auto_aim::ArmorName::outpost) ? -15.0f * CV_PI / 180.0f : 15.0f * CV_PI / 180.0f;
        float sin_pitch = std::sin(pitch);
        float cos_pitch = std::cos(pitch);

        std::vector<Eigen::Vector3f> base_points = {
            {0.0f, armor_width / 2.0f, armor_height / 2.0f},
            {0.0f, -armor_width / 2.0f, armor_height / 2.0f},
            {0.0f, -armor_width / 2.0f, -armor_height / 2.0f},
            {0.0f, armor_width / 2.0f, -armor_height / 2.0f}
        };

        std::vector<rerun::Position3D> armor_vertices;
        std::vector<rerun::components::Color> armor_colors;
        for (const auto& xyza : armor_xyza_list) {
          float sin_yaw = std::sin(xyza[3]);
          float cos_yaw = std::cos(xyza[3]);
          Eigen::Matrix3f R_armor2world;
          R_armor2world << 
              cos_yaw * cos_pitch, -sin_yaw, cos_yaw * sin_pitch,
              sin_yaw * cos_pitch,  cos_yaw, sin_yaw * sin_pitch,
                       -sin_pitch,     0.0f,           cos_pitch;
                       
          Eigen::Vector3f center((float)xyza[0], (float)xyza[1], (float)xyza[2]);
          std::vector<Eigen::Vector3f> p_world(4);
          for (int i = 0; i < 4; i++) {
              p_world[i] = R_armor2world * base_points[i] + center;
          }
          
          auto add_vertex = [&](int i) {
              armor_vertices.push_back({p_world[i].x(), p_world[i].y(), p_world[i].z()});
              armor_colors.push_back({0, 255, 0, 150});
          };
          
          add_vertex(0); add_vertex(1); add_vertex(2);
          add_vertex(0); add_vertex(2); add_vertex(3);
        }
        
        // 可视化预测击打点 (从 planner 获取)
        Eigen::Vector4d aim_xyza = planner.debug_xyza;
        std::vector<rerun::Position3D> aim_vertices;
        std::vector<rerun::components::Color> aim_colors;
        {
            float aim_yaw = aim_xyza[3];
            float aim_sin_yaw = std::sin(aim_yaw);
            float aim_cos_yaw = std::cos(aim_yaw);
            Eigen::Matrix3f aim_R_armor2world;
            aim_R_armor2world << 
                aim_cos_yaw * cos_pitch, -aim_sin_yaw, aim_cos_yaw * sin_pitch,
                aim_sin_yaw * cos_pitch,  aim_cos_yaw, aim_sin_yaw * sin_pitch,
                             -sin_pitch,         0.0f,               cos_pitch;
                             
            Eigen::Vector3f aim_center((float)aim_xyza[0], (float)aim_xyza[1], (float)aim_xyza[2]);
            std::vector<Eigen::Vector3f> aim_p_world(4);
            for (int i = 0; i < 4; i++) {
                aim_p_world[i] = aim_R_armor2world * base_points[i] + aim_center;
            }
            
            auto add_aim_vertex = [&](int i) {
                aim_vertices.push_back({aim_p_world[i].x(), aim_p_world[i].y(), aim_p_world[i].z()});
                aim_colors.push_back({255, 0, 0, 150});
            };
            
            add_aim_vertex(0); add_aim_vertex(1); add_aim_vertex(2);
            add_aim_vertex(0); add_aim_vertex(2); add_aim_vertex(3);
        }
        
        std::vector<rerun::Position3D> vehicle_center = {
            {(float)target->ekf_x()[0], (float)target->ekf_x()[2], (float)target->ekf_x()[4]}
        };
        std::vector<rerun::Vector3D> vehicle_velocity = {
            {(float)target->ekf_x()[1], (float)target->ekf_x()[3], (float)target->ekf_x()[5]}
        };
        
        if (do_rerun) {
          rec->log("world/target/armors", rerun::Clear::FLAT);
          rec->log("world/target/armors_direction", rerun::Clear::FLAT);
          rec->log("world/target/aim_point", rerun::Clear::FLAT);
          rec->log("world/target/aim_direction", rerun::Clear::FLAT);
          
          if (!armor_vertices.empty()) {
              rec->log("world/target/armors_rect", rerun::Mesh3D(armor_vertices).with_vertex_colors(armor_colors));
          }
          if (!aim_vertices.empty()) {
              rec->log("world/target/aim_rect", rerun::Mesh3D(aim_vertices).with_vertex_colors(aim_colors));
          }
          
          rec->log("world/target/vehicle_center", rerun::Points3D(vehicle_center).with_radii({0.03f}).with_colors({{0, 255, 255}}));
          rec->log("world/target/vehicle_velocity", rerun::Arrows3D::from_vectors(vehicle_velocity).with_origins(vehicle_center).with_colors({{0, 255, 255}}));

          rec->log("scalar/target/w", rerun::Scalars(target->ekf_x()[7])); // 记录目标的旋转角速度w
          rec->log("scalar/target/z", rerun::Scalars(target->ekf_x()[4]));
          rec->log("scalar/target/vz", rerun::Scalars(target->ekf_x()[5]));
        }
          
      } else {
        // 丢失目标时清空绘制，防止屏幕上留着鬼影
        if (do_rerun) {
          rec->log("world/target/armors", rerun::Clear::FLAT);
          rec->log("world/target/armors_direction", rerun::Clear::FLAT);
          rec->log("world/target/armors_rect", rerun::Clear::FLAT);
          rec->log("world/target/aim_point", rerun::Clear::FLAT);
          rec->log("world/target/aim_direction", rerun::Clear::FLAT);
          rec->log("world/target/aim_rect", rerun::Clear::FLAT);
          rec->log("world/target/vehicle_center", rerun::Clear::FLAT);
          rec->log("world/target/vehicle_velocity", rerun::Clear::FLAT);
        }
      }
      // =========================

      rerun_counter++;
      std::this_thread::sleep_for(5ms);
    }
  });

  std::mutex lob_mutex;
  cv::Mat shared_lob_preview;

  auto lob_thread = std::thread([&]() {
    cv::Mat lob_img;
    std::chrono::steady_clock::time_point lob_t;
    while (!quit) {
      lob_camera.read(lob_img, lob_t);
      if (!lob_img.empty()) {
        cv::Mat encoded_preview = video_encoder.push_frame(lob_img);
        {
          std::lock_guard<std::mutex> lock(lob_mutex);
          shared_lob_preview = encoded_preview.clone();
        }
      }
      std::this_thread::sleep_for(1ms);
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

    if (imshow) {
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
      cv::imshow("reprojection", img);

      cv::Mat current_lob_preview;
      {
        std::lock_guard<std::mutex> lock(lob_mutex);
        if (!shared_lob_preview.empty()) {
          current_lob_preview = shared_lob_preview.clone();
        }
      }
      if (!current_lob_preview.empty()) {
        cv::imshow("Video Encoder Preview", current_lob_preview);
      }
    }
    if (rerun) rec->log("scalar/fps", rerun::Scalars((float)fps));
    auto key = cv::waitKey(1);
    if (key == 'q') break;
  }

  quit = true;
  if (plan_thread.joinable()) plan_thread.join();
  if (lob_thread.joinable()) lob_thread.join();
  gimbal.send(false, false, 0, 0, 0, 0, 0, 0);

  return 0;
}