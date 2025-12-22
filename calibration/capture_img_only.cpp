#include <fmt/core.h>

#include <filesystem>
#include <opencv2/opencv.hpp>

#include "io/camera.hpp"
#include "tools/logger.hpp"

const std::string keys =
  "{help h usage ?  |                          | 输出命令行参数说明}"
  "{@config-path c  | configs/calibration.yaml | yaml配置文件路径 }"
  "{output-folder o |      assets/img_only     | 输出文件夹路径   }";

void capture_loop(const std::string & config_path, const std::string & output_folder)
{
  io::Camera camera(config_path);
  cv::Mat img;
  std::chrono::steady_clock::time_point timestamp;

  int count = 0;
  while (true) {
    camera.read(img, timestamp);

    // 复制一份用于显示
    auto img_display = img.clone();

    std::vector<cv::Point2f> centers_2d; 
    
    // 显示时缩小图片尺寸
    cv::resize(img_display, img_display, {}, 0.5, 0.5);

    // 按“s”保存图片，按“q”退出程序
    cv::imshow("Press s to save, q to quit", img_display);
    auto key = cv::waitKey(1);
    if (key == 'q')
      break;
    else if (key != 's')
      continue;

    // 保存图片
    count++;
    auto img_path = fmt::format("{}/{}.jpg", output_folder, count);
    cv::imwrite(img_path, img);
    tools::logger()->info("[{}] Saved image in {}", count, output_folder);
  }
}

int main(int argc, char * argv[])
{
  // 读取命令行参数
  cv::CommandLineParser cli(argc, argv, keys);
  if (cli.has("help")) {
    cli.printMessage();
    return 0;
  }
  auto config_path = cli.get<std::string>(0);
  auto output_folder = cli.get<std::string>("output-folder");

  // 新建输出文件夹
  std::filesystem::create_directory(output_folder);

  // 主循环，只保存图片
  capture_loop(config_path, output_folder);

  return 0;
}