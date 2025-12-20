#include "io/gimbal/gimbal.hpp"
#include "io/xrobot_imu/xrobot_imu.hpp"

#include <chrono>
#include <opencv2/opencv.hpp>
#include <thread>

#include "tools/exiter.hpp"
#include "tools/logger.hpp"
#include "tools/math_tools.hpp"
#include "tools/plotter.hpp"

const std::string keys =
  "{help h usage ? | | 输出命令行参数说明}"
  "{f              | | 是否开火}"
  "{@config-path   | | yaml配置文件路径 }";

using namespace std::chrono_literals;

int main(int argc, char * argv[])
{
  cv::CommandLineParser cli(argc, argv, keys);
  auto test_fire = cli.get<bool>("f");
  auto config_path = cli.get<std::string>("@config-path");
  if (cli.has("help") || !cli.has("@config-path")) {
    cli.printMessage();
    return 0;
  }

  tools::Exiter exiter;
  tools::Plotter plotter;

  // 初始化Gimbal和XrobotImu
  io::Gimbal gimbal(config_path);
  io::XrobotImu imu(config_path);

  auto t0 = std::chrono::steady_clock::now();
  auto last_mode = gimbal.mode();
  uint16_t last_bullet_count = 0;

  auto fire = false;
  auto fire_count = 0;
  auto fire_stamp = std::chrono::steady_clock::now();
  auto first_fired = false;

  while (!exiter.exit()) {
    auto t = std::chrono::steady_clock::now();
    
    // 获取Gimbal状态
    auto mode = gimbal.mode();
    auto gimbal_state = gimbal.state();
    
    // 获取IMU状态（姿态数据）
    auto imu_state = imu.state();
    auto current_euler = imu.euler(t);  // 插值获取当前时刻的欧拉角
    
    // 模式变化检测
    if (mode != last_mode) {
      tools::logger()->info("Gimbal mode changed: {}", gimbal.str(mode));
      last_mode = mode;
    }
    
    // 发射检测
    auto fired = gimbal_state.bullet_count > last_bullet_count;
    last_bullet_count = gimbal_state.bullet_count;
    
    if (!first_fired && fired) {
      first_fired = true;
      tools::logger()->info("Gimbal first fired after: {:.3f}s", tools::delta_time(t, fire_stamp));
    }
    
    // 发射控制逻辑（如果需要测试开火）
    if (test_fire) {
      if (fire && fire_count > 20) {
        // 0.2 s
        fire = false;
        fire_count = 0;
      } else if (!fire && fire_count > 100) {
        // 1s
        fire = true;
        fire_count = 0;
        fire_stamp = t;
        first_fired = false;
      }
      fire_count++;
    }
    
    // 发送控制指令（注意：现在只发送raw_yaw和raw_pitch，目标值设为0）
    // raw_yaw和raw_pitch是当前姿态，从IMU读取
    // 目标yaw, pitch等设为0，表示不需要云台移动
    gimbal.send(
      true,                         // control
      test_fire && fire,           // fire
      current_euler[2],            // raw_yaw（从IMU获取的当前yaw）
      current_euler[1],            // raw_pitch（从IMU获取的当前pitch）
      0.0f,                        // yaw（目标yaw，设为0）
      0.0f,                        // yaw_vel（目标yaw速度，设为0）
      0.0f,                        // yaw_acc（目标yaw加速度，设为0）
      0.0f,                        // pitch（目标pitch，设为0）
      0.0f,                        // pitch_vel（目标pitch速度，设为0）
      0.0f                         // pitch_acc（目标pitch加速度，设为0）
    );
    
    // 准备绘图数据
    nlohmann::json data;
    
    // Gimbal数据
    data["gimbal_mode"] = static_cast<int>(mode);
    data["bullet_speed"] = gimbal_state.bullet_speed;
    data["bullet_count"] = gimbal_state.bullet_count;
    data["fired"] = fired ? 1 : 0;
    data["fire_command"] = (test_fire && fire) ? 1 : 0;
    
    // IMU数据（姿态）
    data["imu_roll"] = current_euler[0];     // roll
    data["imu_pitch"] = current_euler[1];    // pitch
    data["imu_yaw"] = current_euler[2];      // yaw
    
    // 四元数数据
    auto current_q = imu.q(t);
    data["q_w"] = current_q.w();
    data["q_x"] = current_q.x();
    data["q_y"] = current_q.y();
    data["q_z"] = current_q.z();
    
    // 角速度数据
    auto current_gyro = imu.gyro(t);
    data["gyro_x"] = current_gyro[0];
    data["gyro_y"] = current_gyro[1];
    data["gyro_z"] = current_gyro[2];
    
    // 加速度数据
    auto current_accl = imu.accl(t);
    data["accl_x"] = current_accl[0];
    data["accl_y"] = current_accl[1];
    data["accl_z"] = current_accl[2];
    
    // 时间戳
    data["imu_time"] = static_cast<double>(imu_state.time);
    data["imu_sync"] = static_cast<double>(imu_state.sync);
    data["t"] = tools::delta_time(t, t0);
    
    // 发送到绘图器
    plotter.plot(data);
    
    // 控制台输出（可选，用于调试）
    if (static_cast<int>(tools::delta_time(t, t0) * 1000) % 1000 == 0) {
      tools::logger()->info(
        "Mode: {}, Bullet: {}, Yaw: {:.2f}°, Pitch: {:.2f}°",
        gimbal.str(mode),
        gimbal_state.bullet_count,
        current_euler[2] * 180.0 / M_PI,
        current_euler[1] * 180.0 / M_PI
      );
    }
    
    std::this_thread::sleep_for(9ms);
  }
  
  // 退出时发送停止控制指令
  gimbal.send(false, false, 0, 0, 0, 0, 0, 0, 0, 0);
  
  return 0;
}