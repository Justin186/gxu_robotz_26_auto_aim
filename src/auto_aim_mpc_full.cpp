#include <fmt/core.h>

#include <atomic>
#include <chrono>
#include <deque>
#include <mutex>
#include <nlohmann/json.hpp>
#include <opencv2/opencv.hpp>
#include <thread>

#include "io/camera.hpp"
#include "io/gimbal/gimbal.hpp"
#include "tasks/video_encoder/video_encoder.hpp"
#include "tasks/auto_aim/planner/planner.hpp"
#include "tasks/auto_aim/solver.hpp"
#include "tasks/auto_aim/tracker.hpp"
#include "tasks/auto_aim/yolo.hpp"
#include "tools/exiter.hpp"
#include "tools/img_tools.hpp"
#include "tools/math_tools.hpp"
#include "tools/plotter.hpp"
#include "tools/thread_safe_queue.hpp"
#include "tools/recorder.hpp"

using namespace std::chrono_literals;

const std::string keys =
  "{help h usage ? |                        | 输出命令行参数说明}"
  "{rec            | true                   | 是否录制数据}"
  "{camera         | configs/camera.yaml    | 位置参数，yaml配置文件路径 }"
  "{@config-path   | configs/hero.yaml      | 位置参数，yaml配置文件路径 }";

int main(int argc, char * argv[])
{
  tools::Exiter exiter;
  tools::Recorder recorder;

  cv::CommandLineParser cli(argc, argv, keys);
  auto config_path = cli.get<std::string>(0);
  auto record = cli.get<bool>("rec");
  auto camera_config_path = cli.get<std::string>("camera");

  if (cli.has("help") || config_path.empty()) {
    cli.printMessage();
    return 0;
  }

  io::Gimbal gimbal(config_path);
  io::Camera camera(config_path);
  io::Camera lob_camera(camera_config_path);

  auto_aim::YOLO yolo(config_path, false);
  auto_aim::Solver solver(config_path);
  auto_aim::Tracker tracker(config_path, solver);
  auto_aim::Planner planner(config_path);

  tasks::VideoEncoderConfig encoder_config;
  // TODO: 后续如果是双相机，就在 yaml 里读取相应的图传相机配置
  encoder_config.target_bitrate = 80;
  encoder_config.output_fps = 60;       // 利用大带宽重新拉回 60 FPS 流畅度
  
  tasks::VideoEncoder video_encoder(encoder_config, [&](const uint8_t* data, size_t size){
    gimbal.send_video(data, size);

    // static int video_send_count = 0;
    // static auto last_video_send_time = std::chrono::steady_clock::now();
    // video_send_count++;
    // auto now = std::chrono::steady_clock::now();
    // if (std::chrono::duration_cast<std::chrono::seconds>(now - last_video_send_time).count() >= 1) {
    //   tools::logger()->info("[VideoEncoder] Send frequency: {} Hz", video_send_count);
    //   video_send_count = 0;
    //   last_video_send_time = now;
    // }
  });

  tools::ThreadSafeQueue<std::optional<auto_aim::Target>, true> target_queue(1);
  target_queue.push(std::nullopt);

  std::atomic<bool> quit = false;
  auto plan_thread = std::thread([&]() {
    auto t0 = std::chrono::steady_clock::now();
    uint16_t last_bullet_count = 0;

    while (!quit) {
      auto target = target_queue.front();
      auto gs = gimbal.state();
      auto plan = planner.plan(target, gs.bullet_speed, gs.yaw, gs.pitch, gs.yaw_offset, gs.pitch_offset);

      gimbal.send(
        plan.control, plan.fire, plan.v_yaw, plan.yaw_vel, plan.yaw_acc, plan.v_pitch, plan.pitch_vel,
        plan.pitch_acc);

      auto fired = gs.bullet_count > last_bullet_count;
      last_bullet_count = gs.bullet_count;

      std::this_thread::sleep_for(5ms);
    }
  });

  std::mutex lob_mutex;
  cv::Mat shared_lob_preview;

  auto lob_thread = std::thread([&]() {
    cv::Mat lob_img;
    std::chrono::steady_clock::time_point lob_t;
    while (!quit) {
      lob_camera.read(lob_img, lob_t);
      if (!lob_img.empty()) {
        cv::Mat encoded_preview = video_encoder.push_frame(lob_img);
        {
          std::lock_guard<std::mutex> lock(lob_mutex);
          shared_lob_preview = encoded_preview.clone();
        }
      }
      std::this_thread::sleep_for(1ms);
    }
  });

  cv::Mat img;
  std::chrono::steady_clock::time_point t;
  auto last_time = std::chrono::steady_clock::now();
  int frame_count = 0;

  while (!exiter.exit()) {
    camera.read(img, t);
    
    frame_count++;
    auto now = std::chrono::steady_clock::now();
    if (std::chrono::duration<double>(now - last_time).count() >= 1.0) {
      double fps = frame_count / std::chrono::duration<double>(now - last_time).count();
      fmt::print("FPS: {:.2f}\n", fps);
      frame_count = 0;
      last_time = now;
    }
    
    auto q = gimbal.q(t);

    recorder.record(img, q, t);

    solver.set_R_gimbal2world(q);
    auto armors = yolo.detect(img);
    auto targets = tracker.track(armors, t);
    if (!targets.empty())
      target_queue.push(targets.front());
    else
      target_queue.push(std::nullopt);

    auto key = cv::waitKey(1);
    if (key == 'q') break;
  }

  quit = true;
  if (plan_thread.joinable()) plan_thread.join();
  if (lob_thread.joinable()) lob_thread.join();
  gimbal.send(false, false, 0, 0, 0, 0, 0, 0);

  return 0;
}