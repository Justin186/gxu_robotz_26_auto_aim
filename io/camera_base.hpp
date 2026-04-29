#ifndef IO__CAMERA_BASE_HPP
#define IO__CAMERA_BASE_HPP

#include <opencv2/opencv.hpp>
#include <chrono>
#include <string>

namespace io
{

class CameraBase
{
public:
  virtual ~CameraBase() = default;

  // 约束所有派生类（相机）都要提供这样一个函数来获取图像和时间戳
  virtual void read(cv::Mat & img, std::chrono::steady_clock::time_point & timestamp) = 0;

  // 用于标识这是左相机、右相机等
  std::string device_name;
};

}  // namespace io

#endif  // IO__CAMERA_BASE_HPP
