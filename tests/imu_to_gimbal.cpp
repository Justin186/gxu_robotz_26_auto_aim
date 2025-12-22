#include "io/gimbal/gimbal.hpp"
#include "io/xrobot_imu/xrobot_imu.hpp"

#include <chrono>
#include <opencv2/opencv.hpp>
#include <thread>

#include "tools/exiter.hpp"

const std::string keys =
  "{help h usage ? |                   | 输出命令行参数说明}"
  "{@config-path   | configs/hero.yaml | yaml配置文件路径 }";

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

  // 初始化Gimbal和XrobotImu
  io::Gimbal gimbal(config_path);
  io::XrobotImu imu(config_path);

  while (!exiter.exit()) {
    auto t = std::chrono::steady_clock::now();
    
    // 获取IMU状态（姿态数据）
    auto current_euler = imu.euler(t);  // 插值获取当前时刻的欧拉角
    
    // 发送控制指令（注意：现在只发送raw_yaw和raw_pitch，目标值设为0）
    // raw_yaw和raw_pitch是当前姿态，从IMU读取
    // 目标yaw, pitch等设为0，表示不需要云台移动
    gimbal.send(
      true,                         // control
      false,                          // fire
      current_euler[2],            // raw_yaw（从IMU获取的当前yaw）
      current_euler[1],            // raw_pitch（从IMU获取的当前pitch）
      0.0f,                        // yaw（目标yaw，设为0）
      0.0f,                        // yaw_vel（目标yaw速度，设为0）
      0.0f,                        // yaw_acc（目标yaw加速度，设为0）
      0.0f,                        // pitch（目标pitch，设为0）
      0.0f,                        // pitch_vel（目标pitch速度，设为0）
      0.0f                         // pitch_acc（目标pitch加速度，设为0）
    );
    
    std::this_thread::sleep_for(1ms);
  }
  return 0;
}