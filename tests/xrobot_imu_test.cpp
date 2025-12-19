#include "io/xrobot_imu/xrobot_imu.hpp"

#include <chrono>
#include <opencv2/opencv.hpp>
#include <thread>

#include "tools/exiter.hpp"
#include "tools/math_tools.hpp"
#include "tools/plotter.hpp"

const std::string keys =
  "{help h usage ? | | 输出命令行参数说明}"
  "{@config-path   | | yaml配置文件路径 }";

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

  io::XrobotImu imu(config_path);

  auto t0 = std::chrono::steady_clock::now();

  while (!exiter.exit()) {
    auto t = std::chrono::steady_clock::now();
    
    // 获取当前状态
    auto state = imu.state();
    
    // 获取插值后的数据
    auto q = imu.q(t);
    auto euler = imu.euler(t);
    auto gyro = imu.gyro(t);
    auto accl = imu.accl(t);
    
    // 将四元数转换为欧拉角用于对比
    auto q_euler = tools::eulers(q, 2, 1, 0);  // 假设顺序为yaw, pitch, roll
    
    nlohmann::json data;
    
    // 四元数
    data["q_w"] = q.w();
    data["q_x"] = q.x();
    data["q_y"] = q.y();
    data["q_z"] = q.z();
    
    // 欧拉角对比：直接读取 vs 四元数转换
    data["euler_roll"] = euler[0];
    data["euler_pitch"] = euler[1];
    data["euler_yaw"] = euler[2];
    
    data["q_roll"] = q_euler[2];
    data["q_pitch"] = q_euler[1];
    data["q_yaw"] = q_euler[0];
    
    // 角速度
    data["gyro_x"] = gyro[0];
    data["gyro_y"] = gyro[1];
    data["gyro_z"] = gyro[2];
    
    // 加速度
    data["accl_x"] = accl[0];
    data["accl_y"] = accl[1];
    data["accl_z"] = accl[2];
    
    // IMU时间戳
    data["imu_time"] = static_cast<double>(state.time);
    data["imu_sync"] = static_cast<double>(state.sync);
    
    // 程序运行时间
    data["t"] = tools::delta_time(t, t0);
    
    // 发送到绘图器
    plotter.plot(data);
    
    // 控制循环频率
    std::this_thread::sleep_for(1ms);
  }

  return 0;
}