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
  "{imshow         | true                   | 是否显示图像窗口}"
  "{rerun          | true                   | 是否将数据记录到Rerun}"
  "{config-path c  | configs/sentry.yaml    | yaml配置文件路径 }"
  "{start-index s  | 0                      | 视频起始帧下标    }"
  "{end-index e    | 0                      | 视频结束帧下标    }"
  "{@input-path    | assets/sentry/sentry   | avi和txt文件的路径}";

int main(int argc, char * argv[])
{
  tools::Exiter exiter;

  cv::CommandLineParser cli(argc, argv, keys);
  auto input_path = cli.get<std::string>(0);
  if (input_path.empty()) input_path = cli.get<std::string>("@input-path");
  auto config_path = cli.get<std::string>("config-path");
  auto rerun_ip = cli.get<std::string>("ip");
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

  auto_aim::YOLO yolo(config_path, true);
  auto_aim::Solver solver(config_path);
  auto_aim::Tracker tracker(config_path, solver);
  auto_aim::Planner planner(config_path);

  auto yaml = tools::load(config_path);
  auto R_gimbal2imubody_data = tools::read<std::vector<double>>(yaml, "R_gimbal2imubody");
  Eigen::Matrix<double, 3, 3, Eigen::RowMajor> R_gimbal2imubody(R_gimbal2imubody_data.data());

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
      double mock_pitch = eulers[1];

      auto plan = planner.plan(target, 21, mock_yaw, mock_pitch, 0.0, 0.0, current_time);

      Eigen::Matrix3d R_imubody2world = q_gimbal.toRotationMatrix();
      Eigen::Matrix3d R_gimbal2world = R_imubody2world * R_gimbal2imubody;
      
      if (rerun) rec->log("world/gimbal", 
        rerun::Transform3D(
          rerun::Vec3D{0.0f, 0.0f, 0.0f},
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
        rec->log("yaw/plan_yaw_vel", rerun::Scalars(plan.yaw_vel));
        rec->log("yaw/plan_yaw_acc", rerun::Scalars(plan.yaw_acc));
      

        rec->log("pitch/plan_pitch", rerun::Scalars(plan.pitch));
        rec->log("pitch/target_pitch", rerun::Scalars(plan.target_pitch));
        rec->log("pitch/gimbal_pitch", rerun::Scalars(mock_pitch));
        rec->log("pitch/plan_pitch_vel", rerun::Scalars(plan.pitch_vel));
        rec->log("pitch/plan_pitch_acc", rerun::Scalars(plan.pitch_acc));

        // gimbal_roll
        rec->log("roll/gimbal_roll", rerun::Scalars(eulers[2]));

        rec->log("fire/plan_fire", rerun::Scalars(plan.fire ? 1.0f : 0.0f));
        rec->log("fire/duty_cycle", rerun::Scalars(fire_duty));
      }

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
        
        Eigen::Vector4d aim_xyza = planner.debug_xyza();
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
        
        if (rerun) {
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
        }
          
        if (rerun) rec->log("scalar/target/w", rerun::Scalars(target->ekf_x()[7])); 
        if (rerun) rec->log("scalar/target/z", rerun::Scalars(target->ekf_x()[4]));
        if (rerun) rec->log("scalar/target/vz", rerun::Scalars(target->ekf_x()[5]));
      } else {
        if (rerun) {
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

    cv::Mat debug_detection_img;
    auto armors = yolo.detect(img, frame_count, debug_detection_img);
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

    if (!targets.empty()) {
      auto target = targets.front();

      std::vector<Eigen::Vector4d> armor_xyza_list = target.armor_xyza_list();
      for (const Eigen::Vector4d & xyza : armor_xyza_list) {
        auto image_points =
          solver.reproject_armor(xyza.head(3), xyza[3], target.armor_type, target.name);
        tools::draw_points(img, image_points, {0, 255, 0});
      }

      Eigen::Vector4d aim_xyza = planner.debug_xyza();
      auto image_points =
        solver.reproject_armor(aim_xyza.head(3), aim_xyza[3], target.armor_type, target.name);
      tools::draw_points(img, image_points, {0, 0, 255});
    }

    if (rerun) {
      if (!debug_detection_img.empty()) {
        std::vector<uchar> det_encoded;
        cv::imencode(".jpg", debug_detection_img, det_encoded);
        rec->log("video/detection", rerun::EncodedImage::from_bytes(det_encoded));
      }

      std::vector<uchar> img_encoded;
      cv::imencode(".jpg", img, img_encoded);
      rec->log("video/reprojection_offline", rerun::EncodedImage::from_bytes(img_encoded));
    } else if (imshow) {
      cv::resize(img, img, {}, 0.5, 0.5);
      cv::resize(debug_detection_img, debug_detection_img, {}, 0.5, 0.5);
      cv::imshow("detection", debug_detection_img);
      cv::imshow("reprojection_offline", img);
    }
    
    // Playback control
    auto key = cv::waitKey(15); // Approx 30fps
    if (key == 'q') break;
  }

  quit = true;
  // Push a dummy element to wake up the thread if blocked
  PlannerInput dummy; dummy.t = std::chrono::steady_clock::now();
  target_queue.push(dummy);
  if (plan_thread.joinable()) plan_thread.join();

  return 0;
}
