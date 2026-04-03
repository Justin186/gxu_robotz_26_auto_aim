#include <fmt/core.h>

#include <atomic>
#include <chrono>
#include <deque>
#include <fstream>
#include <nlohmann/json.hpp>
#include <opencv2/opencv.hpp>
#include <thread>
#include <rerun.hpp>

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

struct PlannerInput {
  std::optional<auto_aim::Target> target;
  double w;
  double x;
  double y;
  double z;
  std::chrono::steady_clock::time_point t;
};

const std::string keys =
  "{help h usage ? |                        | 输出命令行参数说明}"
  "{ip             | 192.168.1.2            | Rerun 查看器的IP地址}"
  "{f              | true                   | 是否开火}"
  "{imshow         | true                   | 是否显示图像窗口}"
  "{rerun          | true                   | 是否将数据记录到Rerun}"
  "{config-path c  | configs/hero.yaml      | yaml配置文件路径 }"
  "{start-index s  | 0                      | 视频起始帧下标    }"
  "{end-index e    | 0                      | 视频结束帧下标    }"
  "{@input-path    | assets/hero/hero       | avi和txt文件的路径}";

int main(int argc, char * argv[])
{
  tools::Exiter exiter;

  cv::CommandLineParser cli(argc, argv, keys);
  auto input_path = cli.get<std::string>(0);
  if (input_path.empty()) input_path = cli.get<std::string>("@input-path");
  auto config_path = cli.get<std::string>("config-path");
  auto rerun_ip = cli.get<std::string>("ip");
  auto fire = cli.get<bool>("f");
  auto imshow = cli.get<bool>("imshow");
  auto rerun = cli.get<bool>("rerun");
  auto start_index = cli.get<int>("start-index");
  auto end_index = cli.get<int>("end-index");

  if (cli.has("help") || config_path.empty()) {
    cli.printMessage();
    return 0;
  }

  auto video_path = fmt::format("{}.avi", input_path);
  auto text_path = fmt::format("{}.txt", input_path);
  cv::VideoCapture video(video_path);
  std::ifstream text(text_path);

  if (!video.isOpened()) {
    std::cerr << "Failed to open video " << video_path << std::endl;
    return -1;
  }
  if (!text.is_open()) {
    std::cerr << "Failed to open text " << text_path << std::endl;
    return -1;
  }

  std::optional<rerun::RecordingStream> rec; 
  if (rerun) {
    rec.emplace("gxu_auto_aim_debug_offline");
    rec->connect_grpc("rerun+http://" + rerun_ip + ":9876/proxy").exit_on_failure();
  }

  auto_aim::YOLO yolo(config_path, imshow);
  auto_aim::Solver solver(config_path);
  auto_aim::Tracker tracker(config_path, solver);
  auto_aim::Planner planner(config_path);

  auto yaml = tools::load(config_path);
  auto R_gimbal2imubody_data = tools::read<std::vector<double>>(yaml, "R_gimbal2imubody");
  Eigen::Matrix<double, 3, 3, Eigen::RowMajor> R_gimbal2imubody(R_gimbal2imubody_data.data());
  auto t_pitchlink2gimbal_data = tools::read<std::vector<double>>(yaml, "t_pitchlink2gimbal");
  Eigen::Vector3d t_pitchlink2gimbal(t_pitchlink2gimbal_data.data());
  t_pitchlink2gimbal /= 1000.0; // mm to m

  auto fire_duty_window = tools::read<size_t>(yaml, "fire_duty_window", 500);

  tools::ThreadSafeQueue<PlannerInput, true> target_queue(1);

  std::atomic<bool> quit = false;
  auto plan_thread = std::thread([&]() {
    auto t0_wall = std::chrono::steady_clock::now();
    uint16_t last_bullet_count = 0;
    
    std::deque<bool> fire_history;
    const size_t history_max_size = fire_duty_window;

    while (!quit) {
      PlannerInput input;
      // ThreadSafeQueue pop() allows popping without blocking if it was designed with front(). Wait, we need to pop and wait.
      // Wait, thread_safe_queue.hpp pop() takes a reference or returns. We use blocking pop.
      target_queue.pop(input);
      if (quit) break;

      auto target = input.target;
      auto current_time = input.t;
      if (rerun) {
        rec->set_time_duration_secs("offline_time", tools::delta_time(current_time, t0_wall));
      }

      Eigen::Quaterniond q_gimbal(input.w, input.x, input.y, input.z);
      Eigen::Vector3d eulers = tools::eulers(q_gimbal.toRotationMatrix(), 2, 1, 0);
      double mock_yaw = eulers[0];
      double mock_yaw_vel = 0.0;
      double mock_pitch = eulers[1];
      double mock_pitch_vel = 0.0;
      double pseudo_bullet_speed = 28.0;

      auto plan = planner.plan(target, pseudo_bullet_speed, mock_yaw, mock_pitch);

      auto fired = plan.fire && fire;

      Eigen::Matrix3d R_imubody2world = q_gimbal.toRotationMatrix();
      Eigen::Matrix3d R_gimbal2world = R_imubody2world * R_gimbal2imubody;
      Eigen::Vector3d t_gimbal2world = R_gimbal2world * (-t_pitchlink2gimbal);
      
      if (rerun) rec->log("world/gimbal", 
        rerun::Transform3D(
          rerun::Vec3D{(float)t_gimbal2world.x(), (float)t_gimbal2world.y(), (float)t_gimbal2world.z()},
          rerun::Mat3x3({
            (float)R_gimbal2world(0,0), (float)R_gimbal2world(1,0), (float)R_gimbal2world(2,0),
            (float)R_gimbal2world(0,1), (float)R_gimbal2world(1,1), (float)R_gimbal2world(2,1),
            (float)R_gimbal2world(0,2), (float)R_gimbal2world(1,2), (float)R_gimbal2world(2,2)
          })
        ),
        rerun::TransformAxes3D(0.5) 
      );
      
      Eigen::Vector3d forward_world = R_gimbal2world.col(0); 
      forward_world.z() = 0.0; 
      if (forward_world.norm() > 1e-6) forward_world.normalize();
      else forward_world = Eigen::Vector3d(1.0, 0.0, 0.0);

      Eigen::Vector3d local_dir = R_gimbal2world.transpose() * forward_world;
      Eigen::Vector3d world_offset(0.0, 0.0, -0.28);
      Eigen::Vector3d local_offset = R_gimbal2world.transpose() * world_offset;

      std::vector<rerun::components::LineStrip3D> strips;
      strips.push_back(rerun::components::LineStrip3D({
        {(float)local_offset.x(), (float)local_offset.y(), (float)local_offset.z()},
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

      if (rerun) { 
        rec->log("world/gimbal/yaw_line",
          rerun::LineStrips3D(strips).with_colors({{255, 165, 0}})
        );
        rec->log("yaw/plan_yaw", rerun::Scalars(plan.yaw));
        rec->log("yaw/target_yaw", rerun::Scalars(plan.target_yaw));
        rec->log("yaw/gimbal_yaw", rerun::Scalars(mock_yaw));
        rec->log("yaw/gimbal_yaw_vel", rerun::Scalars(mock_yaw_vel));
        rec->log("yaw/plan_yaw_vel", rerun::Scalars(plan.yaw_vel));
        rec->log("yaw/plan_yaw_acc", rerun::Scalars(plan.yaw_acc));
      

        rec->log("pitch/plan_pitch", rerun::Scalars(plan.pitch));
        rec->log("pitch/target_pitch", rerun::Scalars(plan.target_pitch));
        rec->log("pitch/gimbal_pitch", rerun::Scalars(mock_pitch));
        rec->log("pitch/plan_pitch_vel", rerun::Scalars(plan.pitch_vel));
        rec->log("pitch/plan_pitch_acc", rerun::Scalars(plan.pitch_acc));

        rec->log("fire/fired", rerun::Scalars(fired ? 1.0f : 0.0f));
        rec->log("fire/plan_fire", rerun::Scalars(plan.fire ? 1.0f : 0.0f));
        rec->log("fire/duty_cycle", rerun::Scalars(fire_duty));
      }

      if (target.has_value()) {
        std::vector<rerun::Position3D> armor_points;
        auto armor_xyza_list = target->armor_xyza_list();
        for (const auto& xyza : armor_xyza_list) {
          armor_points.push_back({(float)xyza[0], (float)xyza[1], (float)xyza[2]});
        }
        
        Eigen::Vector4d aim_xyza = planner.debug_xyza;
        std::vector<rerun::Position3D> aim_points = {
          {(float)aim_xyza[0], (float)aim_xyza[1], (float)aim_xyza[2]}
        };
        
        if (rerun) rec->log("world/target/armors", rerun::Points3D(armor_points)
          .with_radii({0.05f})
          .with_colors({{0, 255, 0}})); 
        
        if (rerun) rec->log("world/target/aim_point", rerun::Points3D(aim_points)
          .with_radii({0.07f})
          .with_colors({{255, 0, 0}})); 
          
        if (rerun) rec->log("scalar/target/w", rerun::Scalars(target->ekf_x()[7])); 
        if (rerun) rec->log("scalar/target/z", rerun::Scalars(target->ekf_x()[4]));
        if (rerun) rec->log("scalar/target/vz", rerun::Scalars(target->ekf_x()[5]));
      } else {
        if (rerun) rec->log("world/target/armors", rerun::Clear::FLAT);
        if (rerun) rec->log("world/target/aim_point", rerun::Clear::FLAT);
      }
    }
  });

  cv::Mat img;
  auto t0 = std::chrono::steady_clock::now();

  video.set(cv::CAP_PROP_POS_FRAMES, start_index);
  for (int i = 0; i < start_index; i++) {
    double t_file, w, x, y, z;
    text >> t_file >> w >> x >> y >> z;
  }

  for (int frame_count = start_index; !exiter.exit(); frame_count++) {
    if (end_index > 0 && frame_count > end_index) break;

    video.read(img);
    if (img.empty()) break;

    double t_file, w, x, y, z;
    text >> t_file >> w >> x >> y >> z;
    auto timestamp = t0 + std::chrono::microseconds(int(t_file * 1e6));

    Eigen::Quaterniond q(w, x, y, z);
    solver.set_R_gimbal2world(q);

    auto armors = yolo.detect(img, frame_count);
    auto targets = tracker.track(armors, timestamp);
    
    PlannerInput p_input;
    if (!targets.empty()) p_input.target = targets.front();
    else p_input.target = std::nullopt;
    p_input.w = w;
    p_input.x = x;
    p_input.y = y;
    p_input.z = z;
    p_input.t = timestamp;
    target_queue.push(p_input);

    if (imshow) {
      if (!targets.empty()) {
        auto target = targets.front();

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

      cv::resize(img, img, {}, 0.5, 0.5);
      cv::imshow("reprojection_offline", img);
    }
    
    // Playback control
    auto key = cv::waitKey(30); // Approx 30fps
    if (key == 'q') break;
    if (key == ' ') {
      // Pause functionality
      while(cv::waitKey(0) != ' ');
    }
  }

  quit = true;
  // Push a dummy element to wake up the thread if blocked
  PlannerInput dummy; dummy.t = std::chrono::steady_clock::now();
  target_queue.push(dummy);
  if (plan_thread.joinable()) plan_thread.join();

  return 0;
}
