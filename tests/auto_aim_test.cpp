#include <fmt/core.h>

#include <chrono>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <opencv2/opencv.hpp>
#include <optional>

#include "tasks/auto_aim/aimer.hpp"
#include "tasks/auto_aim/solver.hpp"
#include "tasks/auto_aim/tracker.hpp"
#include "tasks/auto_aim/yolo.hpp"
#include "tools/exiter.hpp"
#include "tools/img_tools.hpp"
#include "tools/logger.hpp"
#include "tools/math_tools.hpp"
#include "tools/plotter.hpp"

const std::string keys =
  "{help h usage ? |                   | 输出命令行参数说明 }"
  "{config-path c  | configs/demo.yaml | yaml配置文件的路径}"
  "{start-index s  | 0                 | 视频起始帧下标    }"
  "{end-index e    | 0                 | 视频结束帧下标    }"
  "{@input-path    | assets/demo/demo  | avi和txt文件的路径}";

std::optional<std::string> value_after_prefix(const std::string & arg, const std::string & prefix)
{
  if (arg.rfind(prefix, 0) == 0) return arg.substr(prefix.size());
  return std::nullopt;
}

bool is_option(const char * arg) { return arg != nullptr && arg[0] == '-'; }

std::string get_string_arg(
  int argc, char * argv[], const std::string & long_name, const std::string & short_name,
  const std::string & fallback)
{
  for (int i = 1; i < argc; i++) {
    const std::string arg = argv[i];

    if (auto value = value_after_prefix(arg, long_name + "="); value.has_value()) return *value;
    if (auto value = value_after_prefix(arg, short_name + "="); value.has_value()) return *value;
    if ((arg == long_name || arg == short_name) && i + 1 < argc && !is_option(argv[i + 1])) {
      return argv[i + 1];
    }
  }

  return fallback;
}

int get_int_arg(
  int argc, char * argv[], const std::string & long_name, const std::string & short_name,
  int fallback)
{
  auto value = get_string_arg(argc, argv, long_name, short_name, "");
  if (value.empty()) return fallback;

  try {
    return std::stoi(value);
  } catch (const std::exception &) {
    std::cerr << "Invalid integer for " << long_name << ": " << value << std::endl;
    return fallback;
  }
}

std::string get_input_path(int argc, char * argv[], const std::string & fallback)
{
  for (int i = 1; i < argc; i++) {
    const std::string arg = argv[i];

    if (auto value = value_after_prefix(arg, "@input-path="); value.has_value()) return *value;
    if (auto value = value_after_prefix(arg, "--input-path="); value.has_value()) return *value;
    if ((arg == "@input-path" || arg == "--input-path") && i + 1 < argc && !is_option(argv[i + 1])) {
      return argv[i + 1];
    }

    if (arg.empty() || arg[0] == '-') continue;
    if (arg.rfind("@", 0) == 0) continue;
    return arg;
  }

  return fallback;
}

std::string strip_record_extension(const std::string & input_path)
{
  if (input_path.size() > 4 && input_path.substr(input_path.size() - 4) == ".avi") {
    return input_path.substr(0, input_path.size() - 4);
  }
  if (input_path.size() > 4 && input_path.substr(input_path.size() - 4) == ".txt") {
    return input_path.substr(0, input_path.size() - 4);
  }
  return input_path;
}

bool skip_text_frames(std::ifstream & text, int frame_count)
{
  for (int i = 0; i < frame_count; i++) {
    double t, w, x, y, z;
    if (!(text >> t >> w >> x >> y >> z)) return false;
  }
  return true;
}

bool seek_video(cv::VideoCapture & video, int start_index)
{
  if (start_index <= 0) return true;

  video.set(cv::CAP_PROP_POS_FRAMES, start_index);
  auto current_index = static_cast<int>(video.get(cv::CAP_PROP_POS_FRAMES));
  if (current_index == start_index) return true;

  video.set(cv::CAP_PROP_POS_FRAMES, 0);
  cv::Mat skipped;
  for (int i = 0; i < start_index; i++) {
    if (!video.read(skipped) || skipped.empty()) return false;
  }
  return true;
}

int main(int argc, char * argv[])
{
  // 读取命令行参数
  cv::CommandLineParser cli(argc, argv, keys);
  if (cli.has("help")) {
    cli.printMessage();
    return 0;
  }
  auto input_path = strip_record_extension(get_input_path(argc, argv, cli.get<std::string>(0)));
  auto config_path = get_string_arg(argc, argv, "--config-path", "-c", cli.get<std::string>("config-path"));
  auto start_index = get_int_arg(argc, argv, "--start-index", "-s", cli.get<int>("start-index"));
  auto end_index = get_int_arg(argc, argv, "--end-index", "-e", cli.get<int>("end-index"));

  tools::Plotter plotter;
  tools::Exiter exiter;

  auto video_path = fmt::format("{}.avi", input_path);
  auto text_path = fmt::format("{}.txt", input_path);
  cv::VideoCapture video(video_path);
  std::ifstream text(text_path);

  if (!video.isOpened()) {
    std::cerr << "Failed to open video: " << video_path << std::endl;
    std::cerr << "Pass the record prefix without extension, for example: records/1970-01-01_08-00-40"
              << std::endl;
    return -1;
  }
  if (!text.is_open()) {
    std::cerr << "Failed to open text: " << text_path << std::endl;
    return -1;
  }

  auto_aim::YOLO yolo(config_path, false);
  auto_aim::Solver solver(config_path);
  auto_aim::Tracker tracker(config_path, solver);
  auto_aim::Aimer aimer(config_path);

  cv::Mat img, drawing;
  auto t0 = std::chrono::steady_clock::now();

  auto_aim::Target last_target;
  io::Command last_command;
  double last_t = -1;

  // FPS 相关变量
  auto fps_start_time = std::chrono::steady_clock::now();
  int fps_frame_count = 0;
  double current_fps = 0.0;

  if (!seek_video(video, start_index)) {
    std::cerr << "Failed to seek video to frame " << start_index << std::endl;
    return -1;
  }
  if (!skip_text_frames(text, start_index)) {
    std::cerr << "Failed to seek text to frame " << start_index << std::endl;
    return -1;
  }

  for (int frame_count = start_index; !exiter.exit(); frame_count++) {
    if (end_index > 0 && frame_count > end_index) break;

    video.read(img);
    if (img.empty()) break;

    double t, w, x, y, z;
    if (!(text >> t >> w >> x >> y >> z)) break;
    auto timestamp = t0 + std::chrono::microseconds(int(t * 1e6));

    /// 自瞄核心逻辑

    solver.set_R_gimbal2world({w, x, y, z});

    auto yolo_start = std::chrono::steady_clock::now();
    auto armors = yolo.detect(img, frame_count);

    auto tracker_start = std::chrono::steady_clock::now();
    auto targets = tracker.track(armors, timestamp);

    auto aimer_start = std::chrono::steady_clock::now();
    auto command = aimer.aim(targets, timestamp, 27, false);

    if (
      !targets.empty() && aimer.debug_aim_point.valid &&
      std::abs(command.yaw - last_command.yaw) * 57.3 < 2)
      command.shoot = true;

    if (command.control) last_command = command;
    /// 调试输出

    auto finish = std::chrono::steady_clock::now();
    
    auto dt = tools::delta_time(finish, yolo_start);

    tools::logger()->info(
      "[{}] FPS: {:.1f}, yolo: {:.1f}ms, tracker: {:.1f}ms, aimer: {:.1f}ms", frame_count,
      1/dt,
      tools::delta_time(tracker_start, yolo_start) * 1e3,
      tools::delta_time(aimer_start, tracker_start) * 1e3,
      tools::delta_time(finish, aimer_start) * 1e3);

    tools::draw_text(
      img,
      fmt::format(
        "command is {},{:.2f},{:.2f},shoot:{}", command.control, command.yaw * 57.3,
        command.pitch * 57.3, command.shoot),
      {10, 60}, {154, 50, 205});

    Eigen::Quaternion gimbal_q = {w, x, y, z};
    tools::draw_text(
      img,
      fmt::format(
        "gimbal yaw{:.2f}", (tools::eulers(gimbal_q.toRotationMatrix(), 2, 1, 0) * 57.3)[0]),
      {10, 90}, {255, 255, 255});


    if (!targets.empty()) {
      auto target = targets.front();

      if (last_t == -1) {
        last_target = target;
        last_t = t;
        continue;
      }

      std::vector<Eigen::Vector4d> armor_xyza_list;

      // 当前帧target更新后
      armor_xyza_list = target.armor_xyza_list();
      for (const Eigen::Vector4d & xyza : armor_xyza_list) {
        auto image_points =
          solver.reproject_armor(xyza.head(3), xyza[3], target.armor_type, target.name);
        tools::draw_points(img, image_points, {0, 255, 0});
      }

      // aimer瞄准位置
      auto aim_point = aimer.debug_aim_point;
      Eigen::Vector4d aim_xyza = aim_point.xyza;
      auto image_points =
        solver.reproject_armor(aim_xyza.head(3), aim_xyza[3], target.armor_type, target.name);
      if (aim_point.valid) tools::draw_points(img, image_points, {0, 0, 255});
    }

    cv::resize(img, img, {}, 0.7, 0.7);  // 显示时缩小图片尺寸
    cv::imshow("reprojection", img);
    auto key = cv::waitKey(1);
    if (key == 'q') break;
  }

  return 0;
}
