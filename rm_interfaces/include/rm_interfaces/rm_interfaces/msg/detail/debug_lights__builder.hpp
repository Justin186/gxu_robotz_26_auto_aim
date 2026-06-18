// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rm_interfaces:msg/DebugLights.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__MSG__DETAIL__DEBUG_LIGHTS__BUILDER_HPP_
#define RM_INTERFACES__MSG__DETAIL__DEBUG_LIGHTS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rm_interfaces/msg/detail/debug_lights__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rm_interfaces
{

namespace msg
{

namespace builder
{

class Init_DebugLights_data
{
public:
  Init_DebugLights_data()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::rm_interfaces::msg::DebugLights data(::rm_interfaces::msg::DebugLights::_data_type arg)
  {
    msg_.data = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rm_interfaces::msg::DebugLights msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rm_interfaces::msg::DebugLights>()
{
  return rm_interfaces::msg::builder::Init_DebugLights_data();
}

}  // namespace rm_interfaces

#endif  // RM_INTERFACES__MSG__DETAIL__DEBUG_LIGHTS__BUILDER_HPP_
