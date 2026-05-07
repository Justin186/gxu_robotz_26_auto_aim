#include <fmt/core.h>

#include <chrono>
#include <thread>
#include <fstream>
#include <nlohmann/json.hpp>
#include <opencv2/opencv.hpp>

#include "tasks/auto_aim/yolo.hpp"
#include "tools/exiter.hpp"
#include "tools/logger.hpp"
#include "tools/img_tools.hpp"

const std::string keys =
  "{help h usage ? |                   | 输出命令行参数说明 }"
  "{@input-path    | assets/demo/demo  | avi或图片路径（不带扩展名可带.avi）}" 
  "{config-path c  | configs/demo.yaml | yaml配置文件的路径}";

int main(int argc, char * argv[])
{
  cv::CommandLineParser cli(argc, argv, keys);
  if (cli.has("help")) {
    cli.printMessage();
    return 0;
  }

  auto input_path = cli.get<std::string>(0);
  auto config_path = cli.get<std::string>("config-path");

  // 尝试打开视频，否则尝试读取单张图片
  auto video_path = fmt::format("{}.avi", input_path);
  cv::VideoCapture video(video_path);
  bool use_video = video.isOpened();

  cv::Mat img;
  if (!use_video) {
    img = cv::imread(input_path, cv::IMREAD_COLOR);
    if (img.empty()) {
      tools::logger()->error("无法打开视频({})或图片({})", video_path, input_path);
      return -1;
    }
  }

  // 两个 YOLO 实例
  auto_aim::YOLO yolo1(config_path);
  auto_aim::YOLO yolo2(config_path);

  tools::Exiter exiter;

  const int report_interval = 30;  // 每30帧输出一次统计
  int frame_count = 0;
  double total_time_yolo1 = 0.0;
  double total_time_yolo2 = 0.0;

  while (!exiter.exit()) {
    if (use_video) {
      if (!video.read(img)) break;
    }

    frame_count++;
    // 并行运行两个 yolo 的 detect
    using Armors = decltype(yolo1.detect(img, frame_count));
    Armors armors1, armors2;
    double dt1 = 0.0, dt2 = 0.0;

    std::thread th1([&]() {
      auto s = std::chrono::steady_clock::now();
      armors1 = yolo1.detect(img, frame_count);
      auto e = std::chrono::steady_clock::now();
      dt1 = std::chrono::duration<double>(e - s).count();
    });

    std::thread th2([&]() {
      auto s = std::chrono::steady_clock::now();
      armors2 = yolo2.detect(img, frame_count);
      auto e = std::chrono::steady_clock::now();
      dt2 = std::chrono::duration<double>(e - s).count();
    });

    th1.join();
    th2.join();

    total_time_yolo1 += dt1;
    total_time_yolo2 += dt2;

    if (frame_count % report_interval == 0) {
      double avg_fps1 = report_interval / total_time_yolo1;
      double avg_fps2 = report_interval / total_time_yolo2;
      tools::logger()->info("[frames {}-{}] yolo1 avg {:.2f} fps, yolo2 avg {:.2f} fps",
                           frame_count - report_interval + 1, frame_count, avg_fps1, avg_fps2);
      total_time_yolo1 = 0.0;
      total_time_yolo2 = 0.0;
    }

    // 可视化（可选）：在窗口显示检测结果数量
    tools::draw_text(img, fmt::format("y1:{} y2:{}", armors1.size(), armors2.size()), {10, 40}, {0, 255, 0});
    cv::imshow("two_yolo_fps", img);
    int key = cv::waitKey(1);
    if (key == 'q') break;

    if (!use_video) break; // 单张图片只跑一帧
  }

  return 0;
}
