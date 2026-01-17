#include <fmt/core.h>

#include <chrono>
#include <opencv2/opencv.hpp>
#include <yaml-cpp/yaml.h>
#include <nlohmann/json.hpp>

#include "io/camera.hpp"
#include "tasks/auto_aim/detector.hpp"
#include "tasks/auto_aim/yolo.hpp"
#include "tools/exiter.hpp"
#include "tools/logger.hpp"
#include "tools/math_tools.hpp"
#include "tools/img_tools.hpp"
#include "tools/plotter.hpp"

const std::string keys =
  "{help h usage ? |                        | 输出命令行参数说明 }"
  "{@config-path   | configs/sentry.yaml    | yaml配置文件的路径}"
  "{tradition t    | true                   | 是否使用传统方法识别}";

constexpr double LIGHTBAR_LENGTH = 56e-3;     // m
constexpr double BIG_ARMOR_WIDTH = 230e-3;    // m
constexpr double SMALL_ARMOR_WIDTH = 135e-3;  // m

const std::vector<cv::Point3f> BIG_ARMOR_POINTS{
  {0, BIG_ARMOR_WIDTH / 2, LIGHTBAR_LENGTH / 2},
  {0, -BIG_ARMOR_WIDTH / 2, LIGHTBAR_LENGTH / 2},
  {0, -BIG_ARMOR_WIDTH / 2, -LIGHTBAR_LENGTH / 2},
  {0, BIG_ARMOR_WIDTH / 2, -LIGHTBAR_LENGTH / 2}};
const std::vector<cv::Point3f> SMALL_ARMOR_POINTS{
  {0, SMALL_ARMOR_WIDTH / 2, LIGHTBAR_LENGTH / 2},
  {0, -SMALL_ARMOR_WIDTH / 2, LIGHTBAR_LENGTH / 2},
  {0, -SMALL_ARMOR_WIDTH / 2, -LIGHTBAR_LENGTH / 2},
  {0, SMALL_ARMOR_WIDTH / 2, -LIGHTBAR_LENGTH / 2}};

int main(int argc, char * argv[])
{
  // 读取命令行参数
  cv::CommandLineParser cli(argc, argv, keys);
  if (cli.has("help")) {
    cli.printMessage();
    return 0;
  }
  auto config_path = cli.get<std::string>(0);
  auto yaml = YAML::LoadFile(config_path);
  auto camera_matrix_data = yaml["camera_matrix"].as<std::vector<double>>();
  auto distort_coeffs_data = yaml["distort_coeffs"].as<std::vector<double>>();
  cv::Mat camera_matrix = cv::Mat(3, 3, CV_64F, camera_matrix_data.data()).clone();
  cv::Mat distort_coeffs = cv::Mat(distort_coeffs_data).clone();
  auto use_tradition = cli.get<bool>("tradition");
  nlohmann::json data;

  tools::Exiter exiter;
  tools::Plotter plotter;

  io::Camera camera(config_path);
  auto_aim::Detector detector(config_path, false);
  auto_aim::YOLO yolo(config_path, true);

  std::chrono::steady_clock::time_point timestamp;

  while (!exiter.exit()) {
    cv::Mat img;
    std::list<auto_aim::Armor> armors;

    camera.read(img, timestamp);

    if (img.empty()) break;

    auto last = std::chrono::steady_clock::now();

    if (use_tradition)
      armors = detector.detect(img);
    else
      armors = yolo.detect(img);

    if (!armors.empty()) {
      auto & armor = armors.front();

      const auto & object_points =
        (armor.type == auto_aim::ArmorType::big) ? BIG_ARMOR_POINTS : SMALL_ARMOR_POINTS;

      cv::Vec3d rvec, tvec;
      cv::solvePnP(
        object_points, armor.points, camera_matrix, distort_coeffs, rvec, tvec, false,
        cv::SOLVEPNP_IPPE);

      double distance = std::sqrt(tvec[0]*tvec[0] + tvec[1]*tvec[1] + tvec[2]*tvec[2]);

      tools::draw_text(
        img,
        fmt::format(
          "tvec: {:.2f} {:.2f} {:.2f} rvec: {:.2f} {:.2f} {:.2f}", tvec[0], tvec[1], tvec[2], rvec[0], rvec[1], rvec[2]),
        {10, 48}, {255, 255, 255},1.5,4);

      tools::draw_text(
        img,
        fmt::format("Distance: {:.2f} m", distance),
        {10, 80}, {0, 255, 0},2,8);

      auto info = fmt::format(
        "{:.2f} {:.2f} {:.1f} {:.2f} {} {}", armor.ratio, armor.side_ratio,
        armor.rectangular_error * 57.3, armor.confidence, auto_aim::ARMOR_NAMES[armor.name],
        auto_aim::ARMOR_TYPES[armor.type]);
      tools::draw_points(img, armor.points, {0, 255, 0});
      tools::draw_text(img, info, armor.left.bottom, {0, 255, 0});
      data["distance"] = distance;
    }

    cv::resize(img, img, {}, 0.5, 0.5);
    cv::imshow("detection", img);
    auto now = std::chrono::steady_clock::now();
    auto dt = tools::delta_time(now, last);
    tools::logger()->info("{:.2f} fps", 1 / dt);
    plotter.plot(data);

    auto key = cv::waitKey(33);
    if (key == 'q') break;
  }

  return 0;
}