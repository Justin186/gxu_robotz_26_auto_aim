#include <chrono>
#include <nlohmann/json.hpp>
#include <opencv2/opencv.hpp>
#include <thread>
#include <deque>

#include "io/gimbal/gimbal.hpp"
#include "tools/exiter.hpp"
#include "tools/math_tools.hpp"
#include "tools/plotter.hpp"

using namespace std::chrono_literals;

const std::string keys =
  "{help h usage ? |                     | 输出命令行参数说明}"
  "{delta-angle a  |          8          | yaw轴delta角,单位度}"
  "{circle      c  |         0.5         | 三角波的周期,单位秒}"
  "{amplitude   A  |          7          | 圆形轨迹的幅度,单位度}"
  "{period      T  |          4          | 圆形轨迹的周期,单位秒}"
  "{signal-mode m  |        circle       | 发送信号的模式}"
  "{axis        x  |         yaw         | 发送信号的轴}"
  "{@config-path   | configs/sentry.yaml | 位置参数，yaml配置文件路径 }";

int main(int argc, char * argv[])
{
  cv::CommandLineParser cli(argc, argv, keys);
  auto config_path = cli.get<std::string>(0);
  auto delta_angle = cli.get<double>("delta-angle");
  auto circle = cli.get<double>("circle");
  auto amplitude = cli.get<double>("amplitude");    // 圆形轨迹幅度
  auto period = cli.get<double>("period");          // 圆形轨迹周期
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
  double slice = circle * 200;  // 切片数 = 周期 * 帧率
  auto dangle = delta_angle / slice;
  double cmd_angle = init_angle;

  int axis_index = axis == "yaw" ? 0 : 1;  // 0 for yaw, 1 for pitch

  double error = 0;
  int count = 0;

  // // 让云台归零并等待5s
  // gimbal.send(false, false, 0, 0, 0, 0, 0, 0);
  // std::this_thread::sleep_for(5s);

  // 历史数据存储（用于计算角加速度）
  std::deque<double> yaw_vel_history;    // yaw角速度历史（rad/s）
  std::deque<double> pitch_vel_history;  // pitch角速度历史（rad/s）
  std::deque<std::chrono::steady_clock::time_point> time_history; // 时间戳历史
  
  const size_t HISTORY_SIZE = 10;  // 滑动窗口大小
  
  // 命令的角速度和角加速度（根据信号模式计算）
  double cmd_yaw_vel = 0;      // 命令的yaw角速度
  double cmd_yaw_acc = 0;      // 命令的yaw角加速度
  double cmd_pitch_vel = 0;    // 命令的pitch角速度
  double cmd_pitch_acc = 0;    // 命令的pitch角加速度

  double t = 0;
  double dt = 0.005;  // 5ms, 模拟200fps

  auto t0 = std::chrono::steady_clock::now();
  
  // 上次命令角度，用于计算命令角速度
  double last_cmd_yaw = 0;
  double last_cmd_pitch = 0;
  auto last_cmd_time = std::chrono::steady_clock::now();

  while (!exiter.exit()) {
    nlohmann::json data;
    auto current_time = std::chrono::steady_clock::now();

    std::this_thread::sleep_for(5ms);

    // 获取云台状态
    auto gimbal_state = gimbal.state();
    Eigen::Quaterniond q = gimbal.q(current_time);
    Eigen::Vector3d eulers = tools::eulers(q, 2, 1, 0);
    
    double gimbal_yaw = eulers[0];    // 弧度
    double gimbal_pitch = eulers[1];  // 弧度
    
    // 从云台状态获取角速度（单位：rad/s）
    double gimbal_yaw_vel = gimbal_state.yaw_vel;    // 实际yaw角速度(rad/s)
    double gimbal_pitch_vel = gimbal_state.pitch_vel; // 实际pitch角速度(rad/s)

    // 更新历史数据用于计算角加速度
    yaw_vel_history.push_back(gimbal_yaw_vel);
    pitch_vel_history.push_back(gimbal_pitch_vel);
    time_history.push_back(current_time);
    
    // 保持历史数据大小
    if (yaw_vel_history.size() > HISTORY_SIZE) {
      yaw_vel_history.pop_front();
      pitch_vel_history.pop_front();
      time_history.pop_front();
    }
    
    // 计算实际角加速度
    double gimbal_yaw_acc = 0;
    double gimbal_pitch_acc = 0;
    
    if (yaw_vel_history.size() >= 2) {
      // 计算角加速度的函数
      if (yaw_vel_history.size() >= 2) {
        double vel_diff = yaw_vel_history.back() - yaw_vel_history.front();
        auto time_diff = std::chrono::duration<double>(time_history.back() - time_history.front()).count();
        if (time_diff > 0) {
          gimbal_yaw_acc = vel_diff / time_diff;  // rad/s²
        }
      }
      
      if (pitch_vel_history.size() >= 2) {
        double vel_diff = pitch_vel_history.back() - pitch_vel_history.front();
        auto time_diff = std::chrono::duration<double>(time_history.back() - time_history.front()).count();
        if (time_diff > 0) {
          gimbal_pitch_acc = vel_diff / time_diff;  // rad/s²
        }
      }
    }

    // 三角波模式
    if (signal_mode == "triangle_wave") {
      double cmd_yaw = 0, current_pitch = 0;
      auto now = std::chrono::steady_clock::now();
      double time_diff = std::chrono::duration<double>(now - last_cmd_time).count();
      
      if (count == slice) {
        cmd_angle = init_angle;
        // 重置到初始位置
        if (axis_index == 0) {
          cmd_yaw = cmd_angle / 57.3;
          cmd_yaw_vel = (cmd_yaw - last_cmd_yaw) / time_diff;
          last_cmd_yaw = cmd_yaw;
        } else {
          current_pitch = cmd_angle / 57.3;
          cmd_pitch_vel = (current_pitch - last_cmd_pitch) / time_diff;
          last_cmd_pitch = current_pitch;
        }
        count = 0;
      } else {
        cmd_angle += dangle;
        if (axis_index == 0) {
          cmd_yaw = cmd_angle / 57.3;
          cmd_yaw_vel = dangle / 57.3 / 0.005;  // 转换为rad/s
          cmd_yaw_acc = 0;  // 三角波的角加速度为0（匀速运动）
          last_cmd_yaw = cmd_yaw;
        } else {
          current_pitch = cmd_angle / 57.3;
          cmd_pitch_vel = dangle / 57.3 / 0.005;
          cmd_pitch_acc = 0;
          last_cmd_pitch = current_pitch;
        }
        count++;
      }
      
      last_cmd_time = now;

      // 发送云台控制命令（包括角速度和加速度）
      gimbal.send(true, false, cmd_yaw, cmd_yaw_vel, cmd_yaw_acc, current_pitch, cmd_pitch_vel, cmd_pitch_acc);
      
      // 记录数据 - 全部转换为度
      if (axis_index == 0) {
        data["cmd_yaw"] = cmd_yaw * 57.3;                    // 度
        data["cmd_yaw_vel"] = cmd_yaw_vel * 57.3;               // 度/s（角速度）
        data["cmd_yaw_acc"] = cmd_yaw_acc * 57.3;               // 度/s²（角加速度）
        data["gimbal_yaw"] = gimbal_yaw * 57.3;            // 度
        data["gimbal_yaw_vel"] = gimbal_yaw_vel * 57.3;     // 度/s
        data["gimbal_yaw_acc"] = gimbal_yaw_acc * 57.3;     // 度/s²
      } else {
        data["cmd_pitch"] = current_pitch * 57.3;               // 度
        data["cmd_pitch_vel"] = cmd_pitch_vel * 57.3;           // 度/s
        data["cmd_pitch_acc"] = cmd_pitch_acc * 57.3;           // 度/s²
        data["gimbal_pitch"] = gimbal_pitch * 57.3;        // 度
        data["gimbal_pitch_vel"] = gimbal_pitch_vel * 57.3; // 度/s
        data["gimbal_pitch_acc"] = gimbal_pitch_acc * 57.3; // 度/s²
      }
      data["t"] = tools::delta_time(current_time, t0);
      plotter.plot(data);
    }

    // 阶跃信号模式
    else if (signal_mode == "step") {
      auto now = std::chrono::steady_clock::now();
      double time_diff = std::chrono::duration<double>(now - last_cmd_time).count();
      
      if (count == 300) {
        cmd_angle += delta_angle;
        count = 0;
      }
      
      double cmd_yaw = tools::limit_rad(cmd_angle / 57.3);
      gimbal.send(true, false, cmd_yaw, 0, 0, 0, 0, 0);
      count++;
      
      last_cmd_time = now;
      last_cmd_yaw = cmd_yaw;

      // 记录数据 - 全部转换为度
      data["cmd_yaw"] = cmd_yaw * 57.3;                    // 度
      data["gimbal_yaw"] = gimbal_yaw * 57.3;            // 度
      data["gimbal_yaw_vel"] = gimbal_yaw_vel * 57.3;     // 度/s
      data["gimbal_yaw_acc"] = gimbal_yaw_acc * 57.3;     // 度/s²
      
      plotter.plot(data);
    }

    // 圆形轨迹模式
    else if (signal_mode == "circle") {
      // 计算目标位置
      double yaw_deg = amplitude * std::sin(2 * M_PI * t / period);      // 度
      double pitch_deg = amplitude * std::sin(2 * M_PI * t / period + M_PI / 2); // 度
      
      // 转换为弧度用于发送命令
      double yaw = yaw_deg / 57.3;      // 弧度
      double pitch = pitch_deg / 57.3;  // 弧度
      
      // 计算理论角速度（对时间求导）- 先计算度的变化率，再转换为弧度
      double yaw_vel_deg = amplitude * (2 * M_PI / period) * std::cos(2 * M_PI * t / period);      // 度/s
      double pitch_vel_deg = amplitude * (2 * M_PI / period) * std::cos(2 * M_PI * t / period + M_PI / 2); // 度/s
      
      double yaw_vel = yaw_vel_deg / 57.3;      // rad/s
      double pitch_vel = pitch_vel_deg / 57.3;  // rad/s
      
      // 计算理论角加速度（对时间求二阶导）
      double yaw_acc_deg = -amplitude * std::pow(2 * M_PI / period, 2) * std::sin(2 * M_PI * t / period);    // 度/s²
      double pitch_acc_deg = -amplitude * std::pow(2 * M_PI / period, 2) * std::sin(2 * M_PI * t / period + M_PI / 2); // 度/s²
      
      double yaw_acc = yaw_acc_deg / 57.3;      // rad/s²
      double pitch_acc = pitch_acc_deg / 57.3;  // rad/s²
      
      gimbal.send(true, false, yaw, yaw_vel, yaw_acc, pitch, pitch_vel, pitch_acc);
      t += dt;
      
      if (t >= period) {
          t -= period;
      }

      // 记录数据 - 全部转换为度
      data["t"] = t;
      data["cmd_yaw"] = yaw_deg;                // 度
      data["cmd_yaw_vel"] = yaw_vel_deg;        // 度/s
      data["cmd_yaw_acc"] = yaw_acc_deg;        // 度/s²
      data["cmd_pitch"] = pitch_deg;            // 度
      data["cmd_pitch_vel"] = pitch_vel_deg;    // 度/s
      data["cmd_pitch_acc"] = pitch_acc_deg;    // 度/s²
      data["gimbal_yaw"] = gimbal_yaw * 57.3;     // 度
      data["gimbal_yaw_vel"] = gimbal_yaw_vel * 57.3;  // 度/s
      data["gimbal_yaw_acc"] = gimbal_yaw_acc * 57.3;  // 度/s²
      data["gimbal_pitch"] = gimbal_pitch * 57.3;     // 度
      data["gimbal_pitch_vel"] = gimbal_pitch_vel * 57.3; // 度/s
      data["gimbal_pitch_acc"] = gimbal_pitch_acc * 57.3; // 度/s²
      
      plotter.plot(data);
    }
  }
  
  // 程序退出前发送停止命令
  gimbal.send(false, false, 0, 0, 0, 0, 0, 0);
  return 0;
}