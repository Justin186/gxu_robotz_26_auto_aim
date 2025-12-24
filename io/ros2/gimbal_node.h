#ifndef IO__GIMBALNODE_HPP
#define IO__GIMBALNODE_HPP
#include "io/gimbal/gimbal.hpp"
#include <geometry_msgs/msg/twist.hpp>
#include <rclcpp/rclcpp.hpp>
#include <mutex>


namespace io
{
struct __attribute__((packed)) NavToGimbal
{
    uint8_t head = 0xA5;
    float linear_x;
    float linear_y;
    float linear_z;
    float angular_x;
    float angular_y;
    float angular_z;
    uint16_t crc16;
};

struct __attribute__((packed)) GimbalToNav
{
    uint8_t head = 0xA5;
    uint8_t mode;
    uint8_t hp;
    uint16_t crc16;
};

class GimbalNode : public Gimbal, public rclcpp::Node
{
public:
    GimbalNode(const std::string & config_path);
    ~GimbalNode();
    void send_cmd_vel(const geometry_msgs::msg::Twist::SharedPtr msg);  // 订阅回调函数
    void send(io::VisionToGimbal VisionToGimbal);
private:
    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_subscription_;
    std::mutex mutex_;
    void send(io::NavToGimbal NavToGimbal);

    NavToGimbal nav_tx_data_;
};
}   // namespace io
#endif  // IO__GIMBALNODE_HPP






