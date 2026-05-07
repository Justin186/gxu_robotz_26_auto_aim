#ifndef IO__GIMBALNODE_HPP
#define IO__GIMBALNODE_HPP
#include "io/gimbal/gimbal.hpp"
#include <opencv2/opencv.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <mutex>
#include <memory>
#include <thread>
#include <atomic>


namespace io
{
class ROS2;

class GimbalNode : public Gimbal
{
public:
    GimbalNode(const std::string & config_path);
    ~GimbalNode();
    using Gimbal::send;
    
    void send_cmd_vel(const geometry_msgs::msg::Twist::SharedPtr msg);
    void send_cmd_vel_zero(const geometry_msgs::msg::Twist::SharedPtr msg);
    void send_cmd_vel_debug(const geometry_msgs::msg::Twist::SharedPtr msg);
    bool get_image(cv::Mat & img, std::chrono::steady_clock::time_point & timestamp);
    void clear_image();

    static bool is_move;

private:
    void thread_loop();

    std::mutex mutex_;

    NavToGimbal nav_tx_data_;

    std::shared_ptr<ROS2> ros2_;
    std::unique_ptr<std::thread> thread_;
    std::atomic<bool> node_quit_ = false;
};
}   // namespace io
#endif  // IO__GIMBALNODE_HPP

