#ifndef IO__SUBSCRIBE2SIM_HPP
#define IO__SUBSCRIBE2SIM_HPP

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include "tools/thread_safe_queue.hpp"

namespace io
{
class subscribe2sim
{
public:
  // 使用外部传入的节点
  subscribe2sim(rclcpp::Node::SharedPtr node, const std::string & config_path);
  ~subscribe2sim();

  void subscribe_image(const std::string & topic_name = "image_raw", int queue_size = 10);
  
  // 阻塞等待图像（和 HikRobot 的 read() 行为一致）
  void read(cv::Mat & img, std::chrono::steady_clock::time_point & timestamp);
  
  // 非阻塞尝试获取图像
  bool try_get_image(cv::Mat & img, std::chrono::steady_clock::time_point & timestamp);

private:
  void image_callback(const sensor_msgs::msg::Image::SharedPtr msg);

  struct ImageData
  {
    cv::Mat img;
    std::chrono::steady_clock::time_point timestamp;
  };

  rclcpp::Node::SharedPtr node_;
  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr image_subscription_;
  tools::ThreadSafeQueue<ImageData> image_queue_;
};

}  // namespace io
#endif