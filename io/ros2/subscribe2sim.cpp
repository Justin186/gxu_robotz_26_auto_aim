#include "subscribe2sim.hpp"
#include "tools/yaml.hpp"

namespace io
{

subscribe2sim::subscribe2sim(rclcpp::Node::SharedPtr node, const std::string & config_path)
: node_(node), image_queue_(1)  // 队列大小为1，只保留最新帧
{
  auto yaml = tools::load(config_path);
  auto topic = tools::read<std::string>(yaml, "image_topic", "image_raw");
  subscribe_image(topic);
}

subscribe2sim::~subscribe2sim() = default;

void subscribe2sim::subscribe_image(const std::string & topic_name, int queue_size)
{
  image_subscription_ = node_->create_subscription<sensor_msgs::msg::Image>(
    topic_name, queue_size,
    std::bind(&subscribe2sim::image_callback, this, std::placeholders::_1));
  
  RCLCPP_INFO(node_->get_logger(), "Subscribed to image topic: %s", topic_name.c_str());
}

void subscribe2sim::image_callback(const sensor_msgs::msg::Image::SharedPtr msg)
{
  try {
    auto cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    
    ImageData data;
    data.img = cv_ptr->image.clone();
    data.timestamp = std::chrono::steady_clock::now();
    
    // 清空队列，只保留最新一帧
    image_queue_.clear();
    image_queue_.push(data);
    
  } catch (cv_bridge::Exception& e) {
    RCLCPP_WARN(node_->get_logger(), "cv_bridge error: %s", e.what());
  }
}

// ===== 阻塞读取（和 HikRobot 的 read() 行为一致） =====
void subscribe2sim::read(cv::Mat & img, std::chrono::steady_clock::time_point & timestamp)
{
  // 阻塞等待，直到有新图像
  ImageData data;
  image_queue_.pop(data);  // pop 会阻塞等待
  
  img = data.img;
  timestamp = data.timestamp;
}

// ===== 非阻塞尝试获取 =====
bool subscribe2sim::try_get_image(cv::Mat & img, std::chrono::steady_clock::time_point & timestamp)
{
  if (image_queue_.empty()) {
    return false;
  }
  
  ImageData data;
  image_queue_.pop(data);  // 弹出，取走就不在了
  img = data.img;
  timestamp = data.timestamp;
  return true;
}

}  // namespace io