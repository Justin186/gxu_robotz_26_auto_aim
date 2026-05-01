#include <fmt/core.h>

#include <atomic>
#include <chrono>
#include <deque>
#include <optional>
#include <nlohmann/json.hpp>
#include <opencv2/opencv.hpp>
#include <rerun.hpp>
#include <thread>

#include "io/camera.hpp"
#include "io/gimbal/gimbal.hpp"
#include "io/ros2/gimbal_node.hpp"
#include "io/ros2/ros_camera.hpp"
#include "io/usbcamera/usbcamera.hpp"
#include "tasks/auto_aim/planner/planner.hpp"
#include "tasks/auto_aim/solver.hpp"
#include "tasks/auto_aim/tracker.hpp"
#include "tasks/auto_aim/yolo.hpp"
#include "tasks/omniperception/perceptron.hpp"
#include "tools/exiter.hpp"
#include "tools/img_tools.hpp"
#include "tools/logger.hpp"
#include "tools/math_tools.hpp"
#include "tools/recorder.hpp"
#include "tools/thread_safe_queue.hpp"
#include "tools/yaml.hpp"

using namespace std::chrono_literals;

const std::string keys =
  "{help h usage ? |                        | Show help message}"
  "{ip             | 192.168.1.18           | Rerun viewer IP address}"
  "{f              | true                   | Enable fire}"
  "{imshow         | true                   | Show image window}"
  "{rerun          | false                  | Send data to Rerun}"
  "{@config-path   | configs/sentry.yaml    | Path to config yaml }";

int main(int argc, char * argv[])
{
  tools::Exiter exiter;
  tools::Recorder recorder(30);

  cv::CommandLineParser cli(argc, argv, keys);
  auto config_path = cli.get<std::string>(0);
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
    rec.emplace("gxu_auto_aim_multithread_debug");
    rec->connect_grpc("rerun+http://" + rerun_ip + ":9876/proxy").exit_on_failure();
  }

  io::GimbalNode gimbal(config_path);
  io::Camera camera(config_path);

  std::shared_ptr<io::ROS2> ros2_ptr = gimbal.get_ros2();
  io::ROSCamera ros_cam_left("left", ros2_ptr);
  io::USBCamera usb_cam_right("video0", config_path);
  usb_cam_right.device_name = "right";

  omniperception::Perceptron perceptron(&ros_cam_left, &usb_cam_right, config_path);

  auto_aim::YOLO yolo(config_path, imshow);
  
  // 额外创建两个只做推理不自带imshow弹窗的YOLO实例，专门给左右相机调试可视化使用
  auto_aim::YOLO ros_yolo(config_path, false);
  auto_aim::YOLO usb_yolo(config_path, false);

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

    size_t rerun_counter = 0;
    const size_t rerun_interval = 20;

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

      auto plan = planner.plan(target, gs.bullet_speed, gs.yaw, gs.pitch, current_time);
      bool do_rerun = rerun && (rerun_counter % rerun_interval == 0);

      if (tracker.state() != "lost") {
        first_scan = true;
        gimbal.set_aim_status(true);
        gimbal.send(
          plan.control, plan.fire && fire,
          plan.v_yaw, plan.yaw_vel, plan.yaw_acc,
          plan.v_pitch, plan.pitch_vel, plan.pitch_acc);
        std::this_thread::sleep_for(10ms);
      } else if (tracker.state() == "lost" && !io::GimbalNode::is_move) {
        gimbal.set_aim_status(false);

        bool used_omniperception = false;
        auto detect_results = perceptron.get_detection_queue();
        if (!detect_results.empty()) {
          auto best_result = detect_results.back();
          double yaw = tools::limit_rad((gs.yaw * 57.3 + best_result.delta_yaw * 57.3) / 57.3);
          double pitch = tools::limit_rad((gs.pitch * 57.3 + best_result.delta_pitch * 57.3) / 57.3);
          gimbal.send(true, false, yaw, 0, 0, pitch, 0, 0);
          first_scan = true;
          used_omniperception = true;
          std::this_thread::sleep_for(10ms);
        }

        if (!used_omniperception) {
          if (first_scan) {
            scan_cmd_angle = gs.yaw * 57.3;
            first_scan = false;
          }

          double delta_angle = 60;
          double amplitude = 5.0;
          double period = 1;

          scan_cmd_angle += delta_angle * dt;
          double yaw = tools::limit_rad(scan_cmd_angle / 57.3);
          double pitch = tools::limit_rad(amplitude * std::sin(2 * M_PI * scan_t / period) / 57.3 - 0.1);
          gimbal.send(true, false, yaw, 0, 0, pitch, 0, 0);

          scan_t += dt;
          if (scan_t >= period) {
            scan_t -= period;
          }

          std::this_thread::sleep_for(10ms);
        }
      } else {
        std::this_thread::sleep_for(10ms);
      }

      auto fired = gs.bullet_count > last_bullet_count;
      last_bullet_count = gs.bullet_count;

      auto q_gimbal = gimbal.q(current_time);
      Eigen::Matrix3d R_imubody2world = q_gimbal.toRotationMatrix();
      Eigen::Matrix3d R_gimbal2world = R_imubody2world * R_gimbal2imubody;

      if (do_rerun) {
        rec->log(
          "world/gimbal",
          rerun::Transform3D(
            rerun::Vec3D{0.0f, 0.0f, 0.0f},
            rerun::Mat3x3({
              (float)R_gimbal2world(0, 0), (float)R_gimbal2world(1, 0), (float)R_gimbal2world(2, 0),
              (float)R_gimbal2world(0, 1), (float)R_gimbal2world(1, 1), (float)R_gimbal2world(2, 1),
              (float)R_gimbal2world(0, 2), (float)R_gimbal2world(1, 2), (float)R_gimbal2world(2, 2)
            })
          ),
          rerun::TransformAxes3D(0.5));
      }

      Eigen::Vector3d forward_world = R_gimbal2world.col(0);
      if (forward_world.norm() > 1e-6) {
        forward_world.normalize();
      } else {
        forward_world = Eigen::Vector3d(1.0, 0.0, 0.0);
      }

      Eigen::Vector3d local_dir = R_gimbal2world.transpose() * forward_world;
      Eigen::Vector3d world_offset(0.0, 0.0, 0.0);
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

      if (do_rerun) {
        rec->log(
          "world/gimbal/yaw_line",
          rerun::LineStrips3D(strips).with_colors({{255, 165, 0}}));
        rec->log("yaw/plan_yaw", rerun::Scalars(plan.yaw));
        rec->log("yaw/plan_yaw_offset", rerun::Scalars(plan.v_yaw));
        rec->log("yaw/target_yaw", rerun::Scalars(plan.target_yaw));
        rec->log("yaw/gimbal_yaw", rerun::Scalars(gs.yaw / 57.3));
        rec->log("yaw/gimbal_yaw_vel", rerun::Scalars(gs.yaw_vel));
        rec->log("yaw/plan_yaw_vel", rerun::Scalars(plan.yaw_vel));
        rec->log("yaw/plan_yaw_acc", rerun::Scalars(plan.yaw_acc));

        rec->log("pitch/plan_pitch", rerun::Scalars(plan.pitch));
        rec->log("pitch/plan_pitch_offset", rerun::Scalars(plan.v_pitch));
        rec->log("pitch/target_pitch", rerun::Scalars(plan.target_pitch));
        rec->log("pitch/gimbal_pitch", rerun::Scalars(gs.pitch / 57.3));
        rec->log("pitch/plan_pitch_vel", rerun::Scalars(plan.pitch_vel));
        rec->log("pitch/plan_pitch_acc", rerun::Scalars(plan.pitch_acc));

        rec->log("fire/fired", rerun::Scalars(fired ? 1.0f : 0.0f));
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
        for (const auto & xyza : armor_xyza_list) {
          float sin_yaw = std::sin(xyza[3]);
          float cos_yaw = std::cos(xyza[3]);
          Eigen::Matrix3f R_armor2world;
          R_armor2world <<
            cos_yaw * cos_pitch, -sin_yaw, cos_yaw * sin_pitch,
            sin_yaw * cos_pitch,  cos_yaw, sin_yaw * sin_pitch,
            -sin_pitch, 0.0f, cos_pitch;

          Eigen::Vector3f center((float)xyza[0], (float)xyza[1], (float)xyza[2]);
          std::vector<Eigen::Vector3f> p_world(4);
          for (int i = 0; i < 4; i++) {
            p_world[i] = R_armor2world * base_points[i] + center;
          }

          auto add_vertex = [&](int i) {
            armor_vertices.push_back({p_world[i].x(), p_world[i].y(), p_world[i].z()});
            armor_colors.push_back({0, 255, 0, 150});
          };

          add_vertex(0);
          add_vertex(1);
          add_vertex(2);
          add_vertex(0);
          add_vertex(2);
          add_vertex(3);
        }

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
            -sin_pitch, 0.0f, cos_pitch;

          Eigen::Vector3f aim_center((float)aim_xyza[0], (float)aim_xyza[1], (float)aim_xyza[2]);
          std::vector<Eigen::Vector3f> aim_p_world(4);
          for (int i = 0; i < 4; i++) {
            aim_p_world[i] = aim_R_armor2world * base_points[i] + aim_center;
          }

          auto add_aim_vertex = [&](int i) {
            aim_vertices.push_back({aim_p_world[i].x(), aim_p_world[i].y(), aim_p_world[i].z()});
            aim_colors.push_back({255, 0, 0, 150});
          };

          add_aim_vertex(0);
          add_aim_vertex(1);
          add_aim_vertex(2);
          add_aim_vertex(0);
          add_aim_vertex(2);
          add_aim_vertex(3);
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

          rec->log(
            "world/target/vehicle_center",
            rerun::Points3D(vehicle_center).with_radii({0.03f}).with_colors({{0, 255, 255}}));
          rec->log(
            "world/target/vehicle_velocity",
            rerun::Arrows3D::from_vectors(vehicle_velocity)
              .with_origins(vehicle_center)
              .with_colors({{0, 255, 255}}));
        }

        if (do_rerun) rec->log("scalar/target/w", rerun::Scalars(target->ekf_x()[7]));
        if (do_rerun) rec->log("scalar/target/z", rerun::Scalars(target->ekf_x()[4]));
        if (do_rerun) rec->log("scalar/target/vz", rerun::Scalars(target->ekf_x()[5]));
      } else {
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

      rerun_counter++;
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
    if (gimbal.nav_state().game_progress == 4) {
      recorder.record(img, q, t);
    }

    solver.set_R_gimbal2world(q);
    auto armors = yolo.detect(img);
    auto targets = tracker.track(armors, t);
    if (!targets.empty()) {
      target_queue.push(targets.front());
    } else {
      target_queue.push(std::nullopt);
    }

    int key = -1;
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

      tools::draw_text(img, fmt::format("FPS: {:.2f}", fps), {10, 30});
      cv::resize(img, img, {}, 0.7, 0.7);
      cv::imshow("reprojection", img);

      // Display ROS Camera and USB Camera
      cv::Mat ros_img;
      std::chrono::steady_clock::time_point ros_ts;
      ros_cam_left.read(ros_img, ros_ts);
      if (!ros_img.empty()) {
        auto ros_armors = ros_yolo.detect(ros_img);
        for (const auto & armor : ros_armors) {
          auto info = fmt::format(
            "{:.2f} {} {} {}", armor.confidence, auto_aim::COLORS[armor.color],
            auto_aim::ARMOR_NAMES[armor.name], auto_aim::ARMOR_TYPES[armor.type]);
          tools::draw_points(ros_img, armor.points, {0, 255, 0});
          tools::draw_text(ros_img, info, armor.center, {0, 255, 0});
        }
        cv::resize(ros_img, ros_img, {}, 0.7, 0.7);
        cv::imshow("ros_cam_left", ros_img);
      }

      cv::Mat usb_img;
      std::chrono::steady_clock::time_point usb_ts;
      usb_cam_right.read(usb_img, usb_ts);
      if (!usb_img.empty()) {
        auto usb_armors = usb_yolo.detect(usb_img);
        for (const auto & armor : usb_armors) {
          auto info = fmt::format(
            "{:.2f} {} {} {}", armor.confidence, auto_aim::COLORS[armor.color],
            auto_aim::ARMOR_NAMES[armor.name], auto_aim::ARMOR_TYPES[armor.type]);
          tools::draw_points(usb_img, armor.points, {0, 255, 0});
          tools::draw_text(usb_img, info, armor.center, {0, 255, 0});
        }
        cv::resize(usb_img, usb_img, {}, 0.7, 0.7);
        cv::imshow("usb_cam_right", usb_img);
      }

      key = cv::waitKey(1);
    }

    if (rerun) rec->log("scalar/fps", rerun::Scalars((float)fps));
    if (key == 'q') break;
  }

  quit = true;
  if (plan_thread.joinable()) plan_thread.join();
  gimbal.send(false, false, 0, 0, 0, 0, 0, 0);

  return 0;
}
