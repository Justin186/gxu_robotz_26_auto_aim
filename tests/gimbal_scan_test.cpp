#include "io/gimbal/gimbal.hpp"

#include <chrono>
#include <opencv2/opencv.hpp>
#include <thread>
#include <rerun.hpp>

#include "tools/exiter.hpp"
#include "tools/logger.hpp"
#include "tools/math_tools.hpp"
#include "tools/plotter.hpp"

const std::string keys =
  "{help h usage ? |                     | 输出命令行参数说明}"
  "{rerun          | true                | 是否将数据记录到Rerun}"
  "{ip             | 192.168.1.18        | Rerun 查看器的IP地址}"
  "{f              | false               | 是否开火}"
  "{@config-path   | configs/sentry.yaml | yaml配置文件路径 }";

using namespace std::chrono_literals;

int main(int argc, char * argv[])
{
  cv::CommandLineParser cli(argc, argv, keys);
  auto test_fire = cli.get<bool>("f");
  auto rerun_ip = cli.get<std::string>("ip");
  auto rerun = cli.get<bool>("rerun");
  auto config_path = cli.get<std::string>("@config-path");
  if (cli.has("help") || !cli.has("@config-path")) {
    cli.printMessage();
    return 0;
  }

  std::optional<rerun::RecordingStream> rec; 
  if (rerun) {
    rec.emplace("gxu_auto_aim_debug");
    rec->connect_grpc("rerun+http://" + rerun_ip + ":9876/proxy").exit_on_failure();
  }

  tools::Exiter exiter;
  tools::Plotter plotter;
  std::atomic<bool> quit = false;

  io::Gimbal gimbal(config_path);

  auto last_scan_time = std::chrono::steady_clock::now();
  double scan_cmd_angle = 0.0;
  double scan_t = 0.0;
  while (!quit) {
    auto current_time = std::chrono::steady_clock::now();
    double dt = tools::delta_time(current_time, last_scan_time);
    last_scan_time = current_time;

    double delta_angle = 160; // 哨兵扫描：yaw 每秒旋转度数
    double amplitude = 20.0;   // 哨兵扫描：pitch 上下扫动幅度(度)
    double period = 0.6;       // 哨兵扫描：pitch 扫动周期(秒)

    scan_cmd_angle += delta_angle * dt;
    double yaw = tools::limit_rad(scan_cmd_angle / 57.3);
    double yaw_vel = delta_angle / 57.3;
    double yaw_acc = 0.0;
    
    double pitch = tools::limit_rad(amplitude * std::sin(2 * M_PI * scan_t / period) / 57.3 + 0.1);
    double pitch_vel = (amplitude / 57.3) * (2 * M_PI / period) * std::cos(2 * M_PI * scan_t / period);
    double pitch_acc = -(amplitude / 57.3) * std::pow(2 * M_PI / period, 2) * std::sin(2 * M_PI * scan_t / period);
    
    gimbal.send(true, false, yaw, yaw_vel, yaw_acc, pitch, pitch_vel, pitch_acc);

    scan_t += dt;
    if (scan_t >= period) {
        scan_t -= period;
    }

    auto gs = gimbal.state();

    if (rerun) {
      rec->log("yaw/plan_yaw", rerun::Scalars(yaw));
      rec->log("yaw/gimbal_yaw", rerun::Scalars(gs.yaw / 57.3));
      rec->log("pitch/plan_pitch", rerun::Scalars(pitch));
      rec->log("pitch/gimbal_pitch", rerun::Scalars(gs.pitch / 57.3));
    }
    std::this_thread::sleep_for(10ms);
  }

  return 0;
}