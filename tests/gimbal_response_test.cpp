#include <chrono>
#include <nlohmann/json.hpp>
#include <opencv2/opencv.hpp>
#include <thread>

#include "io/gimbal/gimbal.hpp"
#include "tools/exiter.hpp"
#include "tools/logger.hpp"
#include "tools/math_tools.hpp"
#include "tools/plotter.hpp"

using namespace std::chrono_literals;

const std::string keys =
  "{help h usage ? |                     | 输出命令行参数说明}"
  "{delta-angle a  |          8          | yaw轴delta角}"
  "{circle      c  |         0.2         | delta_angle的切片数}"
  "{signal-mode m  |     triangle_wave   | 发送信号的模式}"
  "{axis        x  |         yaw         | 发送信号的轴}"
  "{@config-path   | configs/sentry.yaml | 位置参数，yaml配置文件路径 }";

double yaw_cal(double t)
{
  double A = 7;
  double T = 4;  // s

  return A * std::sin(2 * M_PI * t / T);  // 31是云台yaw初始角度，单位为度
}

double pitch_cal(double t)
{
  double A = 7;
  double T = 4;  // s

  return A * std::sin(2 * M_PI * t / T + M_PI / 2) + 18;  // 18是云台pitch初始角度，单位为度
}

int main(int argc, char * argv[])
{
  cv::CommandLineParser cli(argc, argv, keys);
  auto config_path = cli.get<std::string>(0);
  auto delta_angle = cli.get<double>("delta-angle");
  auto circle = cli.get<double>("circle");
  auto signal_mode = cli.get<std::string>("signal-mode");
  auto axis = cli.get<std::string>("axis");
  if (cli.has("help") || config_path.empty()) {
    cli.printMessage();
    return 0;
  }

  tools::Exiter exiter;
  tools::Plotter plotter;

  io::Gimbal gimbal(config_path);

  auto init_angle = 0;
  double slice = circle * 100;  //切片数=周期*帧率
  auto dangle = delta_angle / slice;
  double cmd_angle = init_angle;

  int axis_index = axis == "yaw" ? 0 : 1;  // 0 for yaw, 1 for pitch

  double error = 0;
  int count = 0;

  // 让云台归零并等待5s
  gimbal.send(false, false, 0, 0, 0, 0, 0, 0);
  std::this_thread::sleep_for(5s);

  double last_cmd_yaw = 0;
  double last_cmd_pitch = 0;

  double t = 0;
  auto last_t = t;
  double dt = 0.005;  // 5ms, 模拟200fps

  auto t0 = std::chrono::steady_clock::now();

  while (!exiter.exit()) {
    nlohmann::json data;
    auto timestamp = std::chrono::steady_clock::now();

    std::this_thread::sleep_for(1ms);

    Eigen::Quaterniond q = gimbal.q(timestamp);
    Eigen::Vector3d eulers = tools::eulers(q, 2, 1, 0);

    // 三角波模式
    if (signal_mode == "triangle_wave") {
      double current_yaw = 0, current_pitch = 0;
      
      if (count == slice) {
        cmd_angle = init_angle;
        // 重置到初始位置
        if (axis_index == 0) {
          current_yaw = cmd_angle / 57.3;
          last_cmd_yaw = current_yaw * 57.3;
        } else {
          current_pitch = cmd_angle / 57.3;
          last_cmd_pitch = current_pitch * 57.3;
        }
        count = 0;
      } else {
        cmd_angle += dangle;
        if (axis_index == 0) {
          current_yaw = cmd_angle / 57.3;
          last_cmd_yaw = current_yaw * 57.3;
        } else {
          current_pitch = cmd_angle / 57.3;
          last_cmd_pitch = current_pitch * 57.3;
        }
        count++;
      }

      // 发送云台控制命令
      gimbal.send(true, false, current_yaw, 0, 0, current_pitch, 0, 0);
      
      // 记录数据
      if (axis_index == 0) {
        data["cmd_yaw"] = current_yaw * 57.3;
        data["last_cmd_yaw"] = last_cmd_yaw;
        data["gimbal_yaw"] = eulers[0] * 57.3;
      } else {
        data["cmd_pitch"] = current_pitch * 57.3;
        data["last_cmd_pitch"] = last_cmd_pitch;
        data["gimbal_pitch"] = eulers[1] * 57.3;
      }
      data["t"] = tools::delta_time(std::chrono::steady_clock::now(), t0);
      plotter.plot(data);
      std::this_thread::sleep_for(8ms);  // 模拟自瞄100fps
    }

    // 阶跃信号模式
    else if (signal_mode == "step") {
      if (count == 300) {
        cmd_angle += delta_angle;
        count = 0;
      }
      
      double current_yaw = tools::limit_rad(cmd_angle / 57.3);
      gimbal.send(true, false, current_yaw, 0, 0, 0, 0, 0);
      count++;

      data["cmd_yaw"] = current_yaw * 57.3;
      data["last_cmd_yaw"] = last_cmd_yaw;
      data["gimbal_yaw"] = eulers[0] * 57.3;
      last_cmd_yaw = current_yaw * 57.3;
      plotter.plot(data);
      std::this_thread::sleep_for(8ms);  // 模拟自瞄100fps
    }

    // 圆形轨迹模式
    else if (signal_mode == "circle") {
      std::cout << "t: " << t << std::endl;
      double yaw = yaw_cal(t) / 57.3;
      double pitch = pitch_cal(t) / 57.3;
      
      gimbal.send(true, false, yaw, 0, 0, pitch, 0, 0);
      t += dt;
      
      if (t - last_t > 2) {
        t += 2.4;
        last_t = t;
      }

      data["t"] = t;
      data["cmd_yaw"] = yaw * 57.3;
      data["cmd_pitch"] = pitch * 57.3;
      data["gimbal_yaw"] = eulers[0] * 57.3;
      data["gimbal_pitch"] = eulers[1] * 57.3;
      plotter.plot(data);
      std::this_thread::sleep_for(9ms);
    }
  }
  
  // 程序退出前发送停止命令
  gimbal.send(false, false, 0, 0, 0, 0, 0, 0);
  return 0;
}