#include <fmt/core.h>

#include <atomic>
#include <chrono>
#include <deque>
#include <nlohmann/json.hpp>
#include <opencv2/opencv.hpp>
#include <thread>

#include "io/camera.hpp"
#include "io/gimbal/gimbal.hpp"
#include "tasks/video_encoder/video_encoder.hpp"
#include "tools/exiter.hpp"
#include "tools/img_tools.hpp"
#include "tools/thread_safe_queue.hpp"
#include "tools/yaml.hpp"

using namespace std::chrono_literals;

const std::string keys =
  "{help h usage ? |                        | 输出命令行参数说明}"
  "{imshow         | true                   | 是否显示图像窗口}"
  "{@config-path   | configs/hero.yaml      | 位置参数，yaml配置文件路径 }";

int main(int argc, char * argv[])
{
  tools::Exiter exiter;

  cv::CommandLineParser cli(argc, argv, keys);
  auto config_path = cli.get<std::string>(0);
  auto imshow = cli.get<bool>("imshow");

  if (cli.has("help") || config_path.empty()) {
    cli.printMessage();
    return 0;
  }

  io::Gimbal gimbal(config_path);
  io::Camera camera(config_path);

  tasks::VideoEncoderConfig encoder_config;
  // TODO: 后续如果是双相机，就在 yaml 里读取相应的图传相机配置
  encoder_config.target_bitrate = 80;
  encoder_config.output_fps = 60;       // 利用大带宽重新拉回 60 FPS 流畅度
  
  tasks::VideoEncoder video_encoder(encoder_config, [&](const uint8_t* data, size_t size){
    gimbal.send_video(data, size);

    static int video_send_count = 0;
    static auto last_video_send_time = std::chrono::steady_clock::now();
    video_send_count++;
    auto now = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::seconds>(now - last_video_send_time).count() >= 1) {
      tools::logger()->info("[VideoEncoder] Send frequency: {} Hz", video_send_count);
      video_send_count = 0;
      last_video_send_time = now;
    }
  });


  std::atomic<bool> quit = false;

  cv::Mat img;
  std::chrono::steady_clock::time_point t;
  auto last_t = std::chrono::steady_clock::now();

  while (!exiter.exit()) {
    camera.read(img, t);

    // 将相机画面推入图传模块进行压缩并发送（零拷贝、内部分片、免阻塞）
    cv::Mat encoded_preview = video_encoder.push_frame(img);

    auto now = std::chrono::steady_clock::now();
    double fps = 1.0 / std::chrono::duration<double>(now - last_t).count();
    last_t = now;

    static int main_loop_count = 0;
    static auto last_main_print = now;
    main_loop_count++;
    if (std::chrono::duration_cast<std::chrono::seconds>(now - last_main_print).count() >= 1) {
      tools::logger()->info("[MainLoop] FPS: {}", main_loop_count);
      main_loop_count = 0;
      last_main_print = now;
    }

    if (imshow) {
      if (!encoded_preview.empty()) {
        cv::imshow("Video Encoder Preview", encoded_preview);
      }
      auto key = cv::waitKey(1);
      if (key == 'q') break;
    }
  }

  quit = true;
  gimbal.send(false, false, 0, 0, 0, 0, 0, 0);

  return 0;
}