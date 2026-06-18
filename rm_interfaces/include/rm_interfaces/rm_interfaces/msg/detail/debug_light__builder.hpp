// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rm_interfaces:msg/DebugLight.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__MSG__DETAIL__DEBUG_LIGHT__BUILDER_HPP_
#define RM_INTERFACES__MSG__DETAIL__DEBUG_LIGHT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rm_interfaces/msg/detail/debug_light__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rm_interfaces
{

namespace msg
{

namespace builder
{

class Init_DebugLight_angle
{
public:
  explicit Init_DebugLight_angle(::rm_interfaces::msg::DebugLight & msg)
  : msg_(msg)
  {}
  ::rm_interfaces::msg::DebugLight angle(::rm_interfaces::msg::DebugLight::_angle_type arg)
  {
    msg_.angle = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rm_interfaces::msg::DebugLight msg_;
};

class Init_DebugLight_ratio
{
public:
  explicit Init_DebugLight_ratio(::rm_interfaces::msg::DebugLight & msg)
  : msg_(msg)
  {}
  Init_DebugLight_angle ratio(::rm_interfaces::msg::DebugLight::_ratio_type arg)
  {
    msg_.ratio = std::move(arg);
    return Init_DebugLight_angle(msg_);
  }

private:
  ::rm_interfaces::msg::DebugLight msg_;
};

class Init_DebugLight_is_light
{
public:
  explicit Init_DebugLight_is_light(::rm_interfaces::msg::DebugLight & msg)
  : msg_(msg)
  {}
  Init_DebugLight_ratio is_light(::rm_interfaces::msg::DebugLight::_is_light_type arg)
  {
    msg_.is_light = std::move(arg);
    return Init_DebugLight_ratio(msg_);
  }

private:
  ::rm_interfaces::msg::DebugLight msg_;
};

class Init_DebugLight_center_x
{
public:
  Init_DebugLight_center_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DebugLight_is_light center_x(::rm_interfaces::msg::DebugLight::_center_x_type arg)
  {
    msg_.center_x = std::move(arg);
    return Init_DebugLight_is_light(msg_);
  }

private:
  ::rm_interfaces::msg::DebugLight msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rm_interfaces::msg::DebugLight>()
{
  return rm_interfaces::msg::builder::Init_DebugLight_center_x();
}

}  // namespace rm_interfaces

#endif  // RM_INTERFACES__MSG__DETAIL__DEBUG_LIGHT__BUILDER_HPP_
