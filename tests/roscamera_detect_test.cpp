#include <opencv2/opencv.hpp>
#include <thread>

#include "io/ros2/ros2.hpp"
#include "tasks/auto_aim/yolo.hpp"
#include "tools/exiter.hpp"
#include "tools/logger.hpp"
#include "tools/math_tools.hpp"

using namespace std::chrono_literals;

const std::string keys =
  "{help h usage ? |                        | output help}"
  "{@config-path   | configs/sentry.yaml    | yaml config path}"
  "{d display      | true                   | display video stream}";

int main(int argc, char * argv[])
{
  cv::CommandLineParser cli(argc, argv, keys);
  if (cli.has("help")) {
    cli.printMessage();
    return 0;
  }
  tools::Exiter exiter;

  auto config_path = cli.get<std::string>(0);
  const bool display = cli.get<bool>("display");

  io::ROS2 ros2;
  auto_aim::YOLO yolo(config_path, true);

  cv::Mat img;
  std::chrono::steady_clock::time_point timestamp;
  auto last_stamp = std::chrono::steady_clock::now();
  while (!exiter.exit()) {
    if (!ros2.get_image(img, timestamp)) {
      std::this_thread::sleep_for(1ms);
      continue;
    }

    yolo.detect(img);

    auto dt = tools::delta_time(timestamp, last_stamp);
    last_stamp = timestamp;

    if (dt > 1e-6) {
      tools::logger()->info("{:.2f} fps", 1 / dt);
    }

    if (!display) continue;
    cv::imshow("ros_img", img);
    if (cv::waitKey(1) == 'q') break;
  }
}
