#include <fmt/core.h>

#include <opencv2/opencv.hpp>

#include <cstdlib>
#include <string>

int main(int argc, char * argv[])
{
  if (argc == 2 && std::string(argv[1]) == "--help") {
    fmt::print("用法: {} yaw pitch roll\n", argv[0]);
    fmt::print("  yaw   单位: degree\n");
    fmt::print("  pitch 单位: degree\n");
    fmt::print("  roll  单位: degree\n");
    return 0;
  }

  if (argc != 4) {
    fmt::print("用法: {} yaw pitch roll\n", argv[0]);
    return 1;
  }

  const double yaw_deg = std::stod(argv[1]);
  const double pitch_deg = std::stod(argv[2]);
  const double roll_deg = std::stod(argv[3]);

  const double yaw = yaw_deg * CV_PI / 180.0;
  const double pitch = pitch_deg * CV_PI / 180.0;
  const double roll = roll_deg * CV_PI / 180.0;

  const double cy = std::cos(yaw);
  const double sy = std::sin(yaw);
  const double cp = std::cos(pitch);
  const double sp = std::sin(pitch);
  const double cr = std::cos(roll);
  const double sr = std::sin(roll);

  const double r00 = -sy * cr + cy * sp * sr;
  const double r01 = sy * sr + cy * sp * cr;
  const double r02 = cy * cp;
  const double r10 = -cy * cr - sy * sp * sr;
  const double r11 = cy * sr - sy * sp * cr;
  const double r12 = -sy * cp;
  const double r20 = -cp * sr;
  const double r21 = -cp * cr;
  const double r22 = sp;

  fmt::print(
    "[{:.18f}, {:.18f}, {:.18f}, {:.18f}, {:.18f}, {:.18f}, {:.18f}, {:.18f}, {:.18f}]\n",
    r00, r01, r02, r10, r11, r12, r20, r21, r22);
}