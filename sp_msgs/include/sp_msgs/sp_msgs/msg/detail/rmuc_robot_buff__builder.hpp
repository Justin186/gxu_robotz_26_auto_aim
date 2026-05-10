// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from sp_msgs:msg/RMUCRobotBuff.idl
// generated code does not contain a copyright notice

#ifndef SP_MSGS__MSG__DETAIL__RMUC_ROBOT_BUFF__BUILDER_HPP_
#define SP_MSGS__MSG__DETAIL__RMUC_ROBOT_BUFF__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "sp_msgs/msg/detail/rmuc_robot_buff__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace sp_msgs
{

namespace msg
{

namespace builder
{

class Init_RMUCRobotBuff_vulnerability_pct
{
public:
  explicit Init_RMUCRobotBuff_vulnerability_pct(::sp_msgs::msg::RMUCRobotBuff & msg)
  : msg_(msg)
  {}
  ::sp_msgs::msg::RMUCRobotBuff vulnerability_pct(::sp_msgs::msg::RMUCRobotBuff::_vulnerability_pct_type arg)
  {
    msg_.vulnerability_pct = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sp_msgs::msg::RMUCRobotBuff msg_;
};

class Init_RMUCRobotBuff_header
{
public:
  Init_RMUCRobotBuff_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RMUCRobotBuff_vulnerability_pct header(::sp_msgs::msg::RMUCRobotBuff::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_RMUCRobotBuff_vulnerability_pct(msg_);
  }

private:
  ::sp_msgs::msg::RMUCRobotBuff msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::sp_msgs::msg::RMUCRobotBuff>()
{
  return sp_msgs::msg::builder::Init_RMUCRobotBuff_header();
}

}  // namespace sp_msgs

#endif  // SP_MSGS__MSG__DETAIL__RMUC_ROBOT_BUFF__BUILDER_HPP_
