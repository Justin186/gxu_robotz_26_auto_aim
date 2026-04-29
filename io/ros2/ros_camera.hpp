#ifndef IO__ROS_CAMERA_HPP
#define IO__ROS_CAMERA_HPP

#include "io/camera_base.hpp"
#include "io/ros2/ros2.hpp"

namespace io
{
// 它伪装成普通的相机，但内部是找 ROS2 系统拿数据
class ROSCamera : public CameraBase
{
public:
  // 需要把负责通信的总管 ROS2 的指针传进来
  ROSCamera(const std::string & name, std::shared_ptr<ROS2> ros2_ptr)
  : ros2_ptr_(ros2_ptr)
  {
    this->device_name = name;
  }

  ~ROSCamera() override = default;

  // 这是当感知系统要图片时执行的方法
  void read(cv::Mat & img, std::chrono::steady_clock::time_point & timestamp) override
  {
    if (ros2_ptr_) {
      // 去 subscribe2nav（已经由 ROS2 包裹）接最新的图
      ros2_ptr_->get_image(img, timestamp);
    }
  }

private:
  std::shared_ptr<ROS2> ros2_ptr_;
};

}  // namespace io

#endif  // IO__ROS_CAMERA_HPP
