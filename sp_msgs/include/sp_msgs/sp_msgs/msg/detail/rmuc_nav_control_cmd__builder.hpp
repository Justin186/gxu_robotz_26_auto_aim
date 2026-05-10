// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from sp_msgs:msg/RMUCNavControlCmd.idl
// generated code does not contain a copyright notice

#ifndef SP_MSGS__MSG__DETAIL__RMUC_NAV_CONTROL_CMD__BUILDER_HPP_
#define SP_MSGS__MSG__DETAIL__RMUC_NAV_CONTROL_CMD__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "sp_msgs/msg/detail/rmuc_nav_control_cmd__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace sp_msgs
{

namespace msg
{

namespace builder
{

class Init_RMUCNavControlCmd_cmd_type
{
public:
  explicit Init_RMUCNavControlCmd_cmd_type(::sp_msgs::msg::RMUCNavControlCmd & msg)
  : msg_(msg)
  {}
  ::sp_msgs::msg::RMUCNavControlCmd cmd_type(::sp_msgs::msg::RMUCNavControlCmd::_cmd_type_type arg)
  {
    msg_.cmd_type = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sp_msgs::msg::RMUCNavControlCmd msg_;
};

class Init_RMUCNavControlCmd_header
{
public:
  Init_RMUCNavControlCmd_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RMUCNavControlCmd_cmd_type header(::sp_msgs::msg::RMUCNavControlCmd::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_RMUCNavControlCmd_cmd_type(msg_);
  }

private:
  ::sp_msgs::msg::RMUCNavControlCmd msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::sp_msgs::msg::RMUCNavControlCmd>()
{
  return sp_msgs::msg::builder::Init_RMUCNavControlCmd_header();
}

}  // namespace sp_msgs

#endif  // SP_MSGS__MSG__DETAIL__RMUC_NAV_CONTROL_CMD__BUILDER_HPP_
