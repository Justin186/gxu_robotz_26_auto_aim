#ifndef IO__GIMBALNODE_HPP
#define IO__GIMBALNODE_HPP
#include "io/gimbal/gimbal.hpp"
#include <geometry_msgs/msg/twist.hpp>
#include <mutex>
#include <memory>
#include <thread>
#include <atomic>


namespace io
{
class ROS2;

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

class GimbalNode : public Gimbal
{
public:
    GimbalNode(const std::string & config_path);
    ~GimbalNode();
    using Gimbal::send;
    
    void send_cmd_vel(const geometry_msgs::msg::Twist::SharedPtr msg);
    void send(io::VisionToGimbal VisionToGimbal);

private:
    std::mutex mutex_;

    NavToGimbal nav_tx_data_;

    std::shared_ptr<ROS2> ros2_;
    std::unique_ptr<std::thread> thread_;
    std::atomic<bool> node_quit_ = false;
};
}   // namespace io
#endif  // IO__GIMBALNODE_HPP






