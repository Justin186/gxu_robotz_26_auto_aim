// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rm_interfaces:msg/GimbalCmd.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__MSG__DETAIL__GIMBAL_CMD__BUILDER_HPP_
#define RM_INTERFACES__MSG__DETAIL__GIMBAL_CMD__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rm_interfaces/msg/detail/gimbal_cmd__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rm_interfaces
{

namespace msg
{

namespace builder
{

class Init_GimbalCmd_fire_advice
{
public:
  explicit Init_GimbalCmd_fire_advice(::rm_interfaces::msg::GimbalCmd & msg)
  : msg_(msg)
  {}
  ::rm_interfaces::msg::GimbalCmd fire_advice(::rm_interfaces::msg::GimbalCmd::_fire_advice_type arg)
  {
    msg_.fire_advice = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rm_interfaces::msg::GimbalCmd msg_;
};

class Init_GimbalCmd_distance
{
public:
  explicit Init_GimbalCmd_distance(::rm_interfaces::msg::GimbalCmd & msg)
  : msg_(msg)
  {}
  Init_GimbalCmd_fire_advice distance(::rm_interfaces::msg::GimbalCmd::_distance_type arg)
  {
    msg_.distance = std::move(arg);
    return Init_GimbalCmd_fire_advice(msg_);
  }

private:
  ::rm_interfaces::msg::GimbalCmd msg_;
};

class Init_GimbalCmd_pitch_diff
{
public:
  explicit Init_GimbalCmd_pitch_diff(::rm_interfaces::msg::GimbalCmd & msg)
  : msg_(msg)
  {}
  Init_GimbalCmd_distance pitch_diff(::rm_interfaces::msg::GimbalCmd::_pitch_diff_type arg)
  {
    msg_.pitch_diff = std::move(arg);
    return Init_GimbalCmd_distance(msg_);
  }

private:
  ::rm_interfaces::msg::GimbalCmd msg_;
};

class Init_GimbalCmd_yaw_diff
{
public:
  explicit Init_GimbalCmd_yaw_diff(::rm_interfaces::msg::GimbalCmd & msg)
  : msg_(msg)
  {}
  Init_GimbalCmd_pitch_diff yaw_diff(::rm_interfaces::msg::GimbalCmd::_yaw_diff_type arg)
  {
    msg_.yaw_diff = std::move(arg);
    return Init_GimbalCmd_pitch_diff(msg_);
  }

private:
  ::rm_interfaces::msg::GimbalCmd msg_;
};

class Init_GimbalCmd_yaw
{
public:
  explicit Init_GimbalCmd_yaw(::rm_interfaces::msg::GimbalCmd & msg)
  : msg_(msg)
  {}
  Init_GimbalCmd_yaw_diff yaw(::rm_interfaces::msg::GimbalCmd::_yaw_type arg)
  {
    msg_.yaw = std::move(arg);
    return Init_GimbalCmd_yaw_diff(msg_);
  }

private:
  ::rm_interfaces::msg::GimbalCmd msg_;
};

class Init_GimbalCmd_pitch
{
public:
  explicit Init_GimbalCmd_pitch(::rm_interfaces::msg::GimbalCmd & msg)
  : msg_(msg)
  {}
  Init_GimbalCmd_yaw pitch(::rm_interfaces::msg::GimbalCmd::_pitch_type arg)
  {
    msg_.pitch = std::move(arg);
    return Init_GimbalCmd_yaw(msg_);
  }

private:
  ::rm_interfaces::msg::GimbalCmd msg_;
};

class Init_GimbalCmd_header
{
public:
  Init_GimbalCmd_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GimbalCmd_pitch header(::rm_interfaces::msg::GimbalCmd::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_GimbalCmd_pitch(msg_);
  }

private:
  ::rm_interfaces::msg::GimbalCmd msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rm_interfaces::msg::GimbalCmd>()
{
  return rm_interfaces::msg::builder::Init_GimbalCmd_header();
}

}  // namespace rm_interfaces

#endif  // RM_INTERFACES__MSG__DETAIL__GIMBAL_CMD__BUILDER_HPP_
