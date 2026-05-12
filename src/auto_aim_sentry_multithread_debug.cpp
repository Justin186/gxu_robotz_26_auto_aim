#include <atomic>
#include <chrono>
#include <deque>
#include <opencv2/opencv.hpp>
#include <optional>
#include <pthread.h>
#include <sched.h>
#include <thread>
#include <rerun.hpp>

#include "io/camera.hpp"
#include "io/ros2/gimbal_node.hpp"
#include "io/usbcamera/usbcamera.hpp"
#include "tasks/auto_aim/planner/planner.hpp"
#include "tasks/auto_aim/solver.hpp"
#include "tasks/auto_aim/tracker.hpp"
#include "tasks/auto_aim/yolo.hpp"
#include "tasks/omniperception/decider.hpp"
#include "tasks/omniperception/perceptron.hpp"
#include "tools/exiter.hpp"
#include "tools/img_tools.hpp"
#include "tools/logger.hpp"
#include "tools/math_tools.hpp"
#include "tools/thread_safe_queue.hpp"
#include "tools/yaml.hpp"

using namespace std::chrono_literals;

namespace
{
void bind_thread_to_cpus(std::thread & thread, std::initializer_list<int> cpus, const char * name)
{
#ifdef __linux__
  cpu_set_t cpuset;
  CPU_ZERO(&cpuset);
  for (int cpu : cpus) {
    CPU_SET(cpu, &cpuset);
  }

  const int ret = pthread_setaffinity_np(thread.native_handle(), sizeof(cpu_set_t), &cpuset);
  if (ret != 0) {
    tools::logger()->warn("[Affinity] Failed to bind {} to CPUs 0-5, errno={}", name, ret);
  } else {
    tools::logger()->info("[Affinity] Bound {} to CPUs 0-5", name);
  }
#else
  (void)thread;
  (void)cpus;
  (void)name;
#endif
}

cv::Mat make_debug_tile(const cv::Mat & src, const std::string & label, const cv::Size & size)
{
  cv::Mat tile(size, CV_8UC3, cv::Scalar(30, 30, 30));
  cv::putText(
    tile, label, cv::Point(20, 40), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0, 255, 255), 2,
    cv::LINE_AA);

  if (src.empty()) {
    cv::putText(
      tile, "No frame", cv::Point(20, 90), cv::FONT_HERSHEY_SIMPLEX, 0.9, cv::Scalar(0, 0, 255),
      2, cv::LINE_AA);
    return tile;
  }

  cv::Mat src_bgr;
  if (src.channels() == 1) {
    cv::cvtColor(src, src_bgr, cv::COLOR_GRAY2BGR);
  } else {
    src_bgr = src;
  }

  const double scale =
    std::min(static_cast<double>(size.width) / src_bgr.cols, static_cast<double>(size.height) / src_bgr.rows);
  const int resized_width = std::max(1, static_cast<int>(src_bgr.cols * scale));
  const int resized_height = std::max(1, static_cast<int>(src_bgr.rows * scale));

  cv::Mat resized;
  cv::resize(src_bgr, resized, cv::Size(resized_width, resized_height));

  const int offset_x = (size.width - resized_width) / 2;
  const int offset_y = (size.height - resized_height) / 2;
  resized.copyTo(tile(cv::Rect(offset_x, offset_y, resized_width, resized_height)));
  cv::rectangle(tile, cv::Rect(0, 0, size.width, size.height), cv::Scalar(80, 80, 80), 2);
  return tile;
}

cv::Mat compose_debug_view(
  const cv::Mat & main_img, const cv::Mat & ros_img, const cv::Mat & usb_img, double fps)
{
  const cv::Size tile_size(640, 360);
  auto main_tile = make_debug_tile(main_img, "Main Camera", tile_size);
  auto ros_tile = make_debug_tile(ros_img, "ROS Camera", tile_size);
  auto usb_tile = make_debug_tile(usb_img, "USB Camera", tile_size);
  auto blank_tile = make_debug_tile(cv::Mat(), "Status", tile_size);

  cv::putText(
    blank_tile, cv::format("Main FPS: %.1f", fps), cv::Point(20, 90), cv::FONT_HERSHEY_SIMPLEX,
    0.9, cv::Scalar(0, 255, 0), 2, cv::LINE_AA);
  cv::putText(
    blank_tile, "Side views refresh in scan mode", cv::Point(20, 140), cv::FONT_HERSHEY_SIMPLEX,
    0.7, cv::Scalar(255, 255, 255), 2, cv::LINE_AA);

  cv::Mat top_row;
  cv::Mat bottom_row;
  cv::hconcat(std::vector<cv::Mat>{main_tile, ros_tile}, top_row);
  cv::hconcat(std::vector<cv::Mat>{usb_tile, blank_tile}, bottom_row);

  cv::Mat canvas;
  cv::vconcat(std::vector<cv::Mat>{top_row, bottom_row}, canvas);
  return canvas;
}

void draw_armor_boxes(cv::Mat & img, const std::list<auto_aim::Armor> & armors, const cv::Scalar & color)
{
  for (const auto & armor : armors) {
    if (armor.points.size() == 4) {
      tools::draw_points(img, armor.points, color, 2);
    } else if (armor.box.width > 0 && armor.box.height > 0) {
      cv::rectangle(img, armor.box, color, 2);
    }
  }
}
}  // namespace

const std::string keys =
  "{help h usage ? |                        | output help}"
  "{@config-path   | configs/sentry.yaml    | yaml config path}"
  "{ip             | 192.168.1.18           | Rerun 查看器的IP地址}"
  "{rerun          | true                   | 是否将数据记录到Rerun}"
  "{imshow         | false                  | 是否将数据记录到Rerun}";

int main(int argc, char * argv[])
{
  tools::Exiter exiter;

  cv::CommandLineParser cli(argc, argv, keys);
  auto config_path = cli.get<std::string>(0);
  auto rerun_ip = cli.get<std::string>("ip");
  auto rerun = cli.get<bool>("rerun");
  auto imshow = cli.get<bool>("imshow");

  if (cli.has("help") || config_path.empty()) {
    cli.printMessage();
    return 0;
  }

  // 读取云台到 IMU 刚体的旋转矩阵（用于正确绘制坐标系）
  auto yaml = tools::load(config_path);
  auto R_gimbal2imubody_data = tools::read<std::vector<double>>(yaml, "R_gimbal2imubody");
  Eigen::Matrix<double, 3, 3, Eigen::RowMajor> R_gimbal2imubody(R_gimbal2imubody_data.data());

  // Rerun 连接
  std::optional<rerun::RecordingStream> rec;
  if (rerun) {
    rec.emplace("gxu_sentry_auto_aim");
    rec->connect_grpc("rerun+http://" + rerun_ip + ":9876/proxy").exit_on_failure();
  }

  io::GimbalNode gimbal(config_path);
  io::Camera camera(config_path);
  io::USBCamera usb_cam_right("video0", config_path);
  usb_cam_right.device_name = "right";

  auto_aim::YOLO yolo(config_path, false);
  auto_aim::Solver solver(config_path);
  auto_aim::Tracker tracker(config_path, solver);
  auto_aim::Planner planner(config_path);
  omniperception::Decider decider(config_path);
  omniperception::Perceptron perceptron(
    [&](cv::Mat & img, std::chrono::steady_clock::time_point & ts) {
      return gimbal.get_image(img, ts);
    },
    [&]() { gimbal.clear_image(); }, &usb_cam_right, config_path);

  tools::ThreadSafeQueue<std::optional<auto_aim::Target>, true> target_queue(1);
  target_queue.push(std::nullopt);
  tools::ThreadSafeQueue<std::list<auto_aim::Armor>, true> main_armor_queue(1);
  main_armor_queue.push({});

  std::atomic<bool> quit = false;
  std::atomic<omniperception::Decider::OmniMode> omni_mode{
    omniperception::Decider::OmniMode::tracking};
  std::atomic<int> main_lost_count = 0;

  // 统计发射占空比相关变量
  auto fire_duty_window = tools::read<size_t>(yaml, "fire_duty_window", 500);
  std::deque<bool> fire_history;
  size_t history_max_size = fire_duty_window;

  auto plan_thread = std::thread([&]() {
    auto last_control_time = std::chrono::steady_clock::now();
    auto last_mode = decider.mode();
    uint16_t last_bullet_count = 0;

    while (!quit) {
      auto target = target_queue.front();
      auto gs = gimbal.state();
      auto now = std::chrono::steady_clock::now();
      const double dt = tools::delta_time(now, last_control_time);
      last_control_time = now;

      const auto requested_mode = omni_mode.load();
      auto current_mode = decider.mode();

      if (requested_mode == omniperception::Decider::OmniMode::tracking &&
          current_mode != omniperception::Decider::OmniMode::tracking) {
        decider.set_mode(omniperception::Decider::OmniMode::tracking);
        current_mode = decider.mode();
      } else if (
        requested_mode == omniperception::Decider::OmniMode::scan &&
        current_mode == omniperception::Decider::OmniMode::tracking) {
        decider.set_mode(omniperception::Decider::OmniMode::scan);
        current_mode = decider.mode();
      }

      if (current_mode == omniperception::Decider::OmniMode::tracking &&
          last_mode != omniperception::Decider::OmniMode::tracking) {
        perceptron.clear_side_buffers();
      }

      // ---------- 调试数据准备 ----------
      auto current_time = std::chrono::steady_clock::now();
      auto q_gimbal = gimbal.q(current_time);
      Eigen::Matrix3d R_imubody2world = q_gimbal.toRotationMatrix();
      Eigen::Matrix3d R_gimbal2world = R_imubody2world * R_gimbal2imubody;

      // 发射占空比计算
      bool fired = gs.bullet_count > last_bullet_count;
      last_bullet_count = gs.bullet_count;

      // 控制指令（用于日志）
      bool current_fire = false;
      bool current_control = false;
      double plan_yaw = 0.0, plan_pitch = 0.0, plan_yaw_vel = 0.0, plan_pitch_vel = 0.0,
             plan_yaw_acc = 0.0, plan_pitch_acc = 0.0;
      double command_yaw = 0.0, command_pitch = 0.0, command_yaw_vel = 0.0,
             command_pitch_vel = 0.0, command_yaw_acc = 0.0, command_pitch_acc = 0.0;
      double target_yaw = 0.0, target_pitch = 0.0;
      double decider_yaw = 0.0, decider_pitch = 0.0;
      bool decider_shoot = false;

      if (current_mode == omniperception::Decider::OmniMode::tracking) {
        auto plan = planner.plan(target, gs.bullet_speed, gs.yaw, gs.pitch);
        current_control = plan.control;
        current_fire = plan.fire;
        plan_yaw = plan.yaw;
        plan_pitch = plan.pitch;
        plan_yaw_vel = plan.yaw_vel;
        plan_pitch_vel = plan.pitch_vel;
        plan_yaw_acc = plan.yaw_acc;
        plan_pitch_acc = plan.pitch_acc;
        command_yaw = plan.yaw;
        command_pitch = -plan.pitch;
        command_yaw_vel = plan.yaw_vel;
        command_pitch_vel = -plan.pitch_vel;
        command_yaw_acc = plan.yaw_acc;
        command_pitch_acc = -plan.pitch_acc;
        if (target.has_value()) {
          target_yaw = plan.target_yaw;
          target_pitch = plan.target_pitch;
        }
        gimbal.set_aim_status(true);
        gimbal.send(
          plan.control, plan.fire, plan.yaw, plan.yaw_vel, plan.yaw_acc, -plan.pitch,
          -plan.pitch_vel, -plan.pitch_acc);
      } else {
        gimbal.set_aim_status(false);
        auto command = decider.decide(gs.yaw, gs.pitch, dt, perceptron);
        current_control = command.control;
        decider_yaw = command.yaw;
        decider_pitch = command.pitch;
        decider_shoot = command.shoot;
        current_fire = command.shoot;
        command_yaw = command.yaw;
        command_pitch = command.pitch;
        if (command.control) {
          gimbal.send(true, command.shoot, command.yaw, 0, 0, command.pitch, 0, 0);
        }
        current_mode = decider.mode();
      }

      // 更新发射占空比历史
      fire_history.push_back(current_fire);
      if (fire_history.size() > history_max_size) fire_history.pop_front();
      double fire_duty = 0.0;
      for (bool f : fire_history) if (f) fire_duty += 1.0;
      fire_duty /= fire_history.size();

      // ======================= Rerun 可视化（每帧均更新，不依赖目标） =======================
      if (rerun) {
        // 1. 云台坐标系（始终显示）
        rec->log("world/gimbal",
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

        // 2. 水平指向线（橙色，始终显示）
        Eigen::Vector3d forward_world = R_gimbal2world.col(0);
        forward_world.z() = 0.0;
        if (forward_world.norm() > 1e-6) forward_world.normalize();
        else forward_world = Eigen::Vector3d(1.0, 0.0, 0.0);
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
        rec->log("world/gimbal/yaw_line",
          rerun::LineStrips3D(strips).with_colors({{255, 165, 0}}));

        // 3. 标量数据（角度、角速度、发射、模式等）
        rec->log("yaw/plan_yaw", rerun::Scalars(plan_yaw));
        rec->log("yaw/target_yaw", rerun::Scalars(target_yaw));
        rec->log("yaw/gimbal_yaw", rerun::Scalars(gs.yaw));
        rec->log("yaw/gimbal_yaw_vel", rerun::Scalars(gs.yaw_vel));
        rec->log("yaw/plan_yaw_vel", rerun::Scalars(plan_yaw_vel));
        rec->log("yaw/plan_yaw_acc", rerun::Scalars(plan_yaw_acc));
        rec->log("yaw/command_yaw", rerun::Scalars(command_yaw));
        rec->log("yaw/command_yaw_vel", rerun::Scalars(command_yaw_vel));
        rec->log("yaw/command_yaw_acc", rerun::Scalars(command_yaw_acc));
      

        rec->log("pitch/plan_pitch", rerun::Scalars(plan_pitch));
        rec->log("pitch/target_pitch", rerun::Scalars(target_pitch));
        rec->log("pitch/gimbal_pitch", rerun::Scalars(-gs.pitch));
        rec->log("pitch/plan_pitch_vel", rerun::Scalars(plan_pitch_vel));
        rec->log("pitch/plan_pitch_acc", rerun::Scalars(plan_pitch_acc));
        rec->log("pitch/command_pitch", rerun::Scalars(command_pitch));
        rec->log("pitch/command_pitch_vel", rerun::Scalars(command_pitch_vel));
        rec->log("pitch/command_pitch_acc", rerun::Scalars(command_pitch_acc));

        rec->log("fire/fired", rerun::Scalars(fired ? 1.0f : 0.0f));
        rec->log("fire/plan_fire", rerun::Scalars(current_fire ? 1.0f : 0.0f));
        rec->log("fire/duty_cycle", rerun::Scalars(fire_duty));
        rec->log("bullet_speed", rerun::Scalars(gs.bullet_speed));
        rec->log("control/enabled", rerun::Scalars(current_control ? 1.0f : 0.0f));

        rec->log("mode/is_tracking", rerun::Scalars(current_mode == omniperception::Decider::OmniMode::tracking ? 1.0f : 0.0f));
        rec->log("mode/is_scan", rerun::Scalars(current_mode == omniperception::Decider::OmniMode::scan ? 1.0f : 0.0f));

        if (current_mode != omniperception::Decider::OmniMode::tracking) {
          rec->log("mode/decider_yaw", rerun::Scalars(decider_yaw));
          rec->log("mode/decider_pitch", rerun::Scalars(decider_pitch));
          rec->log("mode/decider_shoot", rerun::Scalars(decider_shoot ? 1.0f : 0.0f));
        }

        // ========== 目标相关可视化（仅在有目标且处于 tracking 模式时绘制，否则清除） ==========
        if (current_mode == omniperception::Decider::OmniMode::tracking && target.has_value()) {
          auto armor_xyza_list = target->armor_xyza_list();
          float armor_width = (target->armor_type == auto_aim::ArmorType::big) ? 0.230f : 0.135f;
          float armor_height = 0.056f;
          float pitch = (target->name == auto_aim::ArmorName::outpost) ? -15.0f * CV_PI / 180.0f : 15.0f * CV_PI / 180.0f;
          float sin_pitch = std::sin(pitch);
          float cos_pitch = std::cos(pitch);

          std::vector<Eigen::Vector3f> base_points = {
            {0.0f,  armor_width/2.0f,  armor_height/2.0f},
            {0.0f, -armor_width/2.0f,  armor_height/2.0f},
            {0.0f, -armor_width/2.0f, -armor_height/2.0f},
            {0.0f,  armor_width/2.0f, -armor_height/2.0f}
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
            for (int i = 0; i < 4; i++) p_world[i] = R_armor2world * base_points[i] + center;
            auto add_vertex = [&](int i) {
              armor_vertices.push_back({p_world[i].x(), p_world[i].y(), p_world[i].z()});
              armor_colors.push_back({0, 255, 0, 150});
            };
            add_vertex(0); add_vertex(1); add_vertex(2);
            add_vertex(0); add_vertex(2); add_vertex(3);
          }

          // 预测打击点（planner.debug_xyza）
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
            for (int i = 0; i < 4; i++) aim_p_world[i] = aim_R_armor2world * base_points[i] + aim_center;
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

          // 先清除上一帧的目标物体（防止残影），再绘制新的
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

          rec->log("scalar/target/w", rerun::Scalars(target->ekf_x()[7]));
          rec->log("scalar/target/z", rerun::Scalars(target->ekf_x()[4]));
          rec->log("scalar/target/vz", rerun::Scalars(target->ekf_x()[5]));
        } else {
          // 无目标或不在 tracking 模式时，仅清除目标相关可视化，保留云台指向线和标量
          rec->log("world/target/armors", rerun::Clear::FLAT);
          rec->log("world/target/armors_direction", rerun::Clear::FLAT);
          rec->log("world/target/armors_rect", rerun::Clear::FLAT);
          rec->log("world/target/aim_point", rerun::Clear::FLAT);
          rec->log("world/target/aim_direction", rerun::Clear::FLAT);
          rec->log("world/target/aim_rect", rerun::Clear::FLAT);
          rec->log("world/target/vehicle_center", rerun::Clear::FLAT);
          rec->log("world/target/vehicle_velocity", rerun::Clear::FLAT);
        }
      } // end if(rerun)

      omni_mode.store(current_mode);
      last_mode = current_mode;
      std::this_thread::sleep_for(2ms);
    }
  });
  bind_thread_to_cpus(plan_thread, {0, 1, 2, 3, 4, 5, 6, 7}, "plan_thread");

  cv::Mat img;
  std::chrono::steady_clock::time_point timestamp;
  auto last_fps_time = std::chrono::steady_clock::now();
  double avg_fps = 0.0;

  while (!exiter.exit()) {
    camera.read(img, timestamp);
    auto now = std::chrono::steady_clock::now();
    double current_fps = 1.0 / std::chrono::duration<double>(now - last_fps_time).count();
    last_fps_time = now;
    avg_fps = (avg_fps == 0.0) ? current_fps : (avg_fps * 0.95 + current_fps * 0.05);
    auto q = gimbal.q(timestamp);
    solver.set_R_gimbal2world(q);

    auto armors = yolo.detect(img);
    auto targets = tracker.track(armors, timestamp);
    main_armor_queue.push(armors);

    if (!targets.empty()) {
      omni_mode = omniperception::Decider::OmniMode::tracking;
      main_lost_count = 0;
      target_queue.push(targets.front());
    } else {
      main_lost_count++;
      if (main_lost_count.load() >= 25 &&
          omni_mode.load() == omniperception::Decider::OmniMode::tracking) {
        omni_mode = omniperception::Decider::OmniMode::scan;
      }
      target_queue.push(std::nullopt);
    }
    if(imshow) {
      cv::Mat ros_img;
      cv::Mat usb_img;
      auto main_armors = main_armor_queue.front();
      std::list<auto_aim::Armor> ros_armors;
      std::list<auto_aim::Armor> usb_armors;
      perceptron.get_latest_left_image(ros_img);
      perceptron.get_latest_right_image(usb_img);
      perceptron.get_latest_left_armors(ros_armors);
      perceptron.get_latest_right_armors(usb_armors);
      draw_armor_boxes(img, main_armors, {0, 255, 0});
      if (!ros_img.empty()) draw_armor_boxes(ros_img, ros_armors, {0, 255, 0});
      if (!usb_img.empty()) draw_armor_boxes(usb_img, usb_armors, {0, 255, 0});
      auto debug_view = compose_debug_view(img, ros_img, usb_img, avg_fps);
      cv::imshow("sentry_debug", debug_view);
      cv::waitKey(1);
    }

    if (rerun) rec->log("scalar/fps", rerun::Scalars((float)avg_fps));
  }

  quit = true;
  if (plan_thread.joinable()) plan_thread.join();
  gimbal.send(false, false, 0, 0, 0, 0, 0, 0);
  return 0;
}
