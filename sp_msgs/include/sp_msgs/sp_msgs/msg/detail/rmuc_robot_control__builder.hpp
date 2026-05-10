// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from sp_msgs:msg/RMUCRobotControl.idl
// generated code does not contain a copyright notice

#ifndef SP_MSGS__MSG__DETAIL__RMUC_ROBOT_CONTROL__BUILDER_HPP_
#define SP_MSGS__MSG__DETAIL__RMUC_ROBOT_CONTROL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "sp_msgs/msg/detail/rmuc_robot_control__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace sp_msgs
{

namespace msg
{

namespace builder
{

class Init_RMUCRobotControl_chassis_spin
{
public:
  explicit Init_RMUCRobotControl_chassis_spin(::sp_msgs::msg::RMUCRobotControl & msg)
  : msg_(msg)
  {}
  ::sp_msgs::msg::RMUCRobotControl chassis_spin(::sp_msgs::msg::RMUCRobotControl::_chassis_spin_type arg)
  {
    msg_.chassis_spin = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sp_msgs::msg::RMUCRobotControl msg_;
};

class Init_RMUCRobotControl_stop_gimbal_scan
{
public:
  explicit Init_RMUCRobotControl_stop_gimbal_scan(::sp_msgs::msg::RMUCRobotControl & msg)
  : msg_(msg)
  {}
  Init_RMUCRobotControl_chassis_spin stop_gimbal_scan(::sp_msgs::msg::RMUCRobotControl::_stop_gimbal_scan_type arg)
  {
    msg_.stop_gimbal_scan = std::move(arg);
    return Init_RMUCRobotControl_chassis_spin(msg_);
  }

private:
  ::sp_msgs::msg::RMUCRobotControl msg_;
};

class Init_RMUCRobotControl_header
{
public:
  Init_RMUCRobotControl_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RMUCRobotControl_stop_gimbal_scan header(::sp_msgs::msg::RMUCRobotControl::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_RMUCRobotControl_stop_gimbal_scan(msg_);
  }

private:
  ::sp_msgs::msg::RMUCRobotControl msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::sp_msgs::msg::RMUCRobotControl>()
{
  return sp_msgs::msg::builder::Init_RMUCRobotControl_header();
}

}  // namespace sp_msgs

#endif  // SP_MSGS__MSG__DETAIL__RMUC_ROBOT_CONTROL__BUILDER_HPP_
