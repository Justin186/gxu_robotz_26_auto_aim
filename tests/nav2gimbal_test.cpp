#include <chrono>
#include <opencv2/opencv.hpp>

#include "io/ros2/gimbal_node.hpp"

#include "tools/exiter.hpp"
#include "tools/plotter.hpp"

const std::string keys =
  "{help h usage ? |                     | 输出命令行参数说明}"
  "{@config-path   | configs/sentry.yaml | yaml配置文件路径 }";

using namespace std::chrono_literals;

int main(int argc, char * argv[])
{
  cv::CommandLineParser cli(argc, argv, keys);
  auto config_path = cli.get<std::string>("@config-path");
  if (cli.has("help") || !cli.has("@config-path")) {
    cli.printMessage();
    return 0;
  }

  tools::Exiter exiter;
  tools::Plotter plotter;

  io::GimbalNode gimbal(config_path);

  while (!exiter.exit()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  return 0;
}