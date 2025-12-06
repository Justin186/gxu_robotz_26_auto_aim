#include <fmt/core.h>
#include <yaml-cpp/yaml.h>

#include <Eigen/Dense>  // 必须在opencv2/core/eigen.hpp上面
#include <fstream>
#include <opencv2/core/eigen.hpp>
#include <opencv2/opencv.hpp>

#include "tools/img_tools.hpp"
#include "tools/math_tools.hpp"

const std::string keys =
  "{help h usage ? |                             | 输出命令行参数说明}"
  "{config-path c  | configs/calibration_dh.yaml | yaml配置文件路径 }"
  "{@input-folder  | assets/img_with_q           | 输入文件夹路径   }";

std::vector<cv::Point3f> centers_3d(const cv::Size & pattern_size, const float center_distance)
{
  std::vector<cv::Point3f> centers_3d;

  for (int i = 0; i < pattern_size.height; i++)
    for (int j = 0; j < pattern_size.width; j++)
      centers_3d.push_back({j * center_distance, i * center_distance, 0});

  return centers_3d;
}

Eigen::Quaterniond read_q(const std::string & q_path)
{
  std::ifstream q_file(q_path);
  double w, x, y, z;
  q_file >> w >> x >> y >> z;
  return {w, x, y, z};
}

void load(
  const std::string & input_folder, const std::string & config_path,
  std::vector<double> & R_pitchlink2imubody_data, std::vector<double> & t_pitchlink2yawlink_data,
  std::vector<cv::Mat> & R_pitchlink2world_list, std::vector<cv::Mat> & t_pitchlink2world_list,
  std::vector<cv::Mat> & rvecs, std::vector<cv::Mat> & tvecs)
{
  // 读取yaml参数
  auto yaml = YAML::LoadFile(config_path);
  auto pattern_cols = yaml["pattern_cols"].as<int>();
  auto pattern_rows = yaml["pattern_rows"].as<int>();
  auto center_distance_mm = yaml["square"].as<double>();
  R_pitchlink2imubody_data = yaml["R_pitchlink2imubody"].as<std::vector<double>>();
  t_pitchlink2yawlink_data = yaml["t_pitchlink2yawlink"].as<std::vector<double>>();
  
  auto camera_matrix_data = yaml["camera_matrix"].as<std::vector<double>>();
  auto distort_coeffs_data = yaml["distort_coeffs"].as<std::vector<double>>();

  cv::Size pattern_size(pattern_cols, pattern_rows);
  Eigen::Matrix<double, 3, 3, Eigen::RowMajor> R_pitchlink2imubody(R_pitchlink2imubody_data.data());
  Eigen::Map<Eigen::Vector3d> t_pitchlink2yawlink(t_pitchlink2yawlink_data.data());
  cv::Matx33d camera_matrix(camera_matrix_data.data());
  cv::Mat distort_coeffs(distort_coeffs_data);

  for (int i = 1; true; i++) {
    // 读取图片和对应四元数
    auto img_path = fmt::format("{}/{}.jpg", input_folder, i);
    auto q_path = fmt::format("{}/{}.txt", input_folder, i);
    auto img = cv::imread(img_path);
    Eigen::Quaterniond q = read_q(q_path);
    if (img.empty()) break;

    // 计算云台的欧拉角
    // 均认为world、imubody、yawlink在同一点（yaw与pitch旋转轴水平平移相交后的交点），并且坐标系都认为是前左上
    // pitchlink是pitch旋转轴中心，坐标系前左上
    // camera与标定版坐标系都是右下前
    Eigen::Matrix3d R_imubody2world = q.toRotationMatrix(); // IMU机体坐标系到绝对IMU世界坐标系

    Eigen::Matrix3d R_pitchlink2world = R_imubody2world * R_pitchlink2imubody;

    Eigen::Vector3d t_pitchlink2world = R_pitchlink2world * t_pitchlink2yawlink;
    
    
    // 在图片上显示云台的欧拉角，用来检验R_pitchlink2imubody是否正确
    Eigen::Vector3d ypr = tools::eulers(R_pitchlink2world, 2, 1, 0) * 57.3;
    auto drawing = img.clone();
    tools::draw_text(drawing, fmt::format("yaw   {:.2f}", ypr[0]), {40, 40}, {0, 0, 255});
    tools::draw_text(drawing, fmt::format("pitch {:.2f}", ypr[1]), {40, 80}, {0, 0, 255});
    tools::draw_text(drawing, fmt::format("roll  {:.2f}", ypr[2]), {40, 120}, {0, 0, 255});

    // 识别标定板（棋盘格）
    std::vector<cv::Point2f> centers_2d;
    cv::Mat gray;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
    auto success = cv::findChessboardCorners(
      gray, pattern_size, centers_2d,
      cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_NORMALIZE_IMAGE);

    if (success) {
      // 亚像素精确化
      cv::cornerSubPix(
        gray, centers_2d, cv::Size(11, 11), cv::Size(-1, -1),
        cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, 30, 0.001));
    }

    // 显示识别结果
    cv::drawChessboardCorners(drawing, pattern_size, centers_2d, success);
    cv::resize(drawing, drawing, {}, 0.5, 0.5);  // 显示时缩小图片尺寸
    cv::imshow("Press any to continue", drawing);
    cv::waitKey(0);

    // 输出识别结果
    fmt::print("[{}] {}\n", success ? "success" : "failure", img_path);
    if (!success) continue;

    // 计算所需的数据
    cv::Mat t_pitchlink2world_cv;
    cv::eigen2cv(t_pitchlink2world, t_pitchlink2world_cv);
    cv::Mat R_pitchlink2world_cv;
    cv::eigen2cv(R_pitchlink2world, R_pitchlink2world_cv);
    cv::Mat rvec, tvec;
    auto centers_3d_ = centers_3d(pattern_size, center_distance_mm);
    cv::solvePnP(
      centers_3d_, centers_2d, camera_matrix, distort_coeffs, rvec, tvec, false, cv::SOLVEPNP_IPPE);

    // 记录所需的数据
    R_pitchlink2world_list.emplace_back(R_pitchlink2world_cv);
    t_pitchlink2world_list.emplace_back(t_pitchlink2world_cv);
    rvecs.emplace_back(rvec);
    tvecs.emplace_back(tvec);
  }
}

void print_yaml(
  const std::vector<double> & R_pitchlink2imubody_data, const cv::Mat & R_camera2pitchlink,
  const cv::Mat & t_camera2pitchlink, const Eigen::Vector3d & ypr)
{
  YAML::Emitter result;
  std::vector<double> R_camera2pitchlink_data(
    R_camera2pitchlink.begin<double>(), R_camera2pitchlink.end<double>());
  std::vector<double> t_camera2pitchlink_data(
    t_camera2pitchlink.begin<double>(), t_camera2pitchlink.end<double>());

  result << YAML::BeginMap;
  result << YAML::Key << "R_pitchlink2imubody";
  result << YAML::Value << YAML::Flow << R_pitchlink2imubody_data;
  result << YAML::Newline;
  result << YAML::Newline;
  result << YAML::Comment(fmt::format(
    "相机同理想情况的偏角: yaw{:.2f} pitch{:.2f} roll{:.2f} degree", ypr[0], ypr[1], ypr[2]));
  result << YAML::Key << "R_camera2pitchlink";
  result << YAML::Value << YAML::Flow << R_camera2pitchlink_data;
  result << YAML::Key << "t_camera2pitchlink";
  result << YAML::Value << YAML::Flow << t_camera2pitchlink_data;
  result << YAML::Newline;
  result << YAML::EndMap;

  fmt::print("\n{}\n", result.c_str());
}

int main(int argc, char * argv[])
{
  // 读取命令行参数
  cv::CommandLineParser cli(argc, argv, keys);
  if (cli.has("help")) {
    cli.printMessage();
    return 0;
  }
  auto input_folder = cli.get<std::string>(0);
  auto config_path = cli.get<std::string>("config-path");

  // 从输入文件夹中加载标定所需的数据
  std::vector<double> R_pitchlink2imubody_data;
  std::vector<cv::Mat> R_pitchlink2world_list, t_pitchlink2world_list;
  std::vector<double> t_pitchlink2yawlink;
  std::vector<cv::Mat> rvecs, tvecs;
  load(
    input_folder, config_path, R_pitchlink2imubody_data, t_pitchlink2yawlink, R_pitchlink2world_list, t_pitchlink2world_list,
    rvecs, tvecs);

  // 手眼标定
  cv::Mat R_camera2pitchlink, t_camera2pitchlink;
  cv::calibrateHandEye(
    R_pitchlink2world_list, t_pitchlink2world_list, rvecs, tvecs, R_camera2pitchlink, t_camera2pitchlink);
  t_camera2pitchlink /= 1e3;  // mm to m

  // 计算相机同理想情况的偏角
  Eigen::Matrix3d R_camera2pitchlink_eigen;
  cv::cv2eigen(R_camera2pitchlink, R_camera2pitchlink_eigen);
  Eigen::Matrix3d R_pitchlink2ideal{{0, -1, 0}, {0, 0, -1}, {1, 0, 0}};
  Eigen::Matrix3d R_camera2ideal = R_pitchlink2ideal * R_camera2pitchlink_eigen;
  Eigen::Vector3d ypr = tools::eulers(R_camera2ideal, 1, 0, 2) * 57.3;  // degree

  // 输出yaml
  print_yaml(R_pitchlink2imubody_data, R_camera2pitchlink, t_camera2pitchlink, ypr);
}
