#include <fmt/core.h>

#include <atomic>
#include <chrono>
#include <nlohmann/json.hpp>
#include <opencv2/opencv.hpp>
#include <thread>

#include "io/camera.hpp"
#include "io/gimbal/gimbal.hpp"
#include "io/xrobot_imu/xrobot_imu.hpp"
#include "tasks/auto_aim/planner/planner.hpp"
#include "tasks/auto_aim/solver.hpp"
#include "tasks/auto_aim/tracker.hpp"
#include "tasks/auto_aim/yolo.hpp"
#include "tools/exiter.hpp"
#include "tools/img_tools.hpp"
#include "tools/logger.hpp"
#include "tools/math_tools.hpp"
#include "tools/plotter.hpp"
#include "tools/thread_safe_queue.hpp"

using namespace std::chrono_literals;

const std::string keys =
  "{help h usage ? |                        | 输出命令行参数说明}"
  "{@config-path   | configs/sentry.yaml | 位置参数，yaml配置文件路径 }";

int main(int argc, char * argv[])
{
  tools::Exiter exiter;
  tools::Plotter plotter;

  cv::CommandLineParser cli(argc, argv, keys);
  auto config_path = cli.get<std::string>(0);
  if (cli.has("help") || config_path.empty()) {
    cli.printMessage();
    return 0;
  }

  io::Gimbal gimbal(config_path);
  io::XrobotImu imu(config_path);
  io::Camera camera(config_path);

  auto_aim::YOLO yolo(config_path, true);
  auto_aim::Solver solver(config_path);
  auto_aim::Tracker tracker(config_path, solver);

  cv::Mat img;
  std::chrono::steady_clock::time_point t;
  
  std::optional<auto_aim::Target> fixed_target = std::nullopt;

  while (!exiter.exit()) {
    camera.read(img, t);
    
    // 使用IMU获取姿态
    auto q = imu.q(t);

    solver.set_R_gimbal2world(q);
    
    if (!fixed_target.has_value()) {
        auto armors = yolo.detect(img);
        auto targets = tracker.track(armors, t);
        if (!targets.empty()) {
            fixed_target = targets.front();
            tools::logger()->info("Target locked! ID: {}", fixed_target->last_id);
        }
    }

    if (fixed_target) {
      auto target = *fixed_target;

      std::vector<Eigen::Vector4d> armor_xyza_list = target.armor_xyza_list();
      for (const Eigen::Vector4d & xyza : armor_xyza_list) {
        auto image_points =
          solver.reproject_armor(xyza.head(3), xyza[3], target.armor_type, target.name);
        tools::draw_points(img, image_points, {0, 255, 0});
      }
      
      cv::putText(img, "LOCKED (Press 'r' to reset)", {50, 50}, cv::FONT_HERSHEY_SIMPLEX, 1, {0, 0, 255}, 2);
    }

    cv::resize(img, img, {}, 0.5, 0.5);
    cv::imshow("reprojection", img);
    auto key = cv::waitKey(1);
    if (key == 'q') break;
    if (key == 'r') {
        fixed_target = std::nullopt;
        tools::logger()->info("Target reset.");
    }
  }

  gimbal.send(false, false, 0, 0, 0, 0, 0, 0, 0, 0);

  return 0;
}
