// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from sp_msgs:msg/RMUCSentryCmd.idl
// generated code does not contain a copyright notice

#ifndef SP_MSGS__MSG__DETAIL__RMUC_SENTRY_CMD__BUILDER_HPP_
#define SP_MSGS__MSG__DETAIL__RMUC_SENTRY_CMD__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "sp_msgs/msg/detail/rmuc_sentry_cmd__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace sp_msgs
{

namespace msg
{

namespace builder
{

class Init_RMUCSentryCmd_cmd_confirm_respawn
{
public:
  explicit Init_RMUCSentryCmd_cmd_confirm_respawn(::sp_msgs::msg::RMUCSentryCmd & msg)
  : msg_(msg)
  {}
  ::sp_msgs::msg::RMUCSentryCmd cmd_confirm_respawn(::sp_msgs::msg::RMUCSentryCmd::_cmd_confirm_respawn_type arg)
  {
    msg_.cmd_confirm_respawn = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sp_msgs::msg::RMUCSentryCmd msg_;
};

class Init_RMUCSentryCmd_cmd_posture
{
public:
  explicit Init_RMUCSentryCmd_cmd_posture(::sp_msgs::msg::RMUCSentryCmd & msg)
  : msg_(msg)
  {}
  Init_RMUCSentryCmd_cmd_confirm_respawn cmd_posture(::sp_msgs::msg::RMUCSentryCmd::_cmd_posture_type arg)
  {
    msg_.cmd_posture = std::move(arg);
    return Init_RMUCSentryCmd_cmd_confirm_respawn(msg_);
  }

private:
  ::sp_msgs::msg::RMUCSentryCmd msg_;
};

class Init_RMUCSentryCmd_header
{
public:
  Init_RMUCSentryCmd_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RMUCSentryCmd_cmd_posture header(::sp_msgs::msg::RMUCSentryCmd::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_RMUCSentryCmd_cmd_posture(msg_);
  }

private:
  ::sp_msgs::msg::RMUCSentryCmd msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::sp_msgs::msg::RMUCSentryCmd>()
{
  return sp_msgs::msg::builder::Init_RMUCSentryCmd_header();
}

}  // namespace sp_msgs

#endif  // SP_MSGS__MSG__DETAIL__RMUC_SENTRY_CMD__BUILDER_HPP_
