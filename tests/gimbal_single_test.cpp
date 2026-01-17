#include <chrono>
#include <opencv2/opencv.hpp>
#include <thread>

#include "io/gimbal/gimbal.hpp"
#include "tools/exiter.hpp"
#include "tools/math_tools.hpp"

using namespace std::chrono_literals;

const std::string keys =
  "{help h usage ? |                     | 输出命令行参数说明}"
  "{@config-path   | configs/sentry.yaml | 位置参数，yaml配置文件路径 }";

int main(int argc, char * argv[])
{
  cv::CommandLineParser cli(argc, argv, keys);
  auto config_path = cli.get<std::string>(0);
  if (cli.has("help") || config_path.empty()) {
    cli.printMessage();
    return 0;
  }
  tools::Exiter exiter;
  io::Gimbal gimbal(config_path);
  double a;
  while (!exiter.exit()) {
      std::cin >> a;
      gimbal.send(true, false,0, 0, 0, a/57.3, 0, 0);
      gimbal.send(true, false,0, 0, 0, 0, 0, 0);
    }
  // 程序退出前发送停止命令
  gimbal.send(false, false, 0, 0, 0, 0, 0, 0);
  return 0;
}