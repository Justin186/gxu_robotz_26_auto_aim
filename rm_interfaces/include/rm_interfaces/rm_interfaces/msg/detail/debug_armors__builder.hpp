// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rm_interfaces:msg/DebugArmors.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__MSG__DETAIL__DEBUG_ARMORS__BUILDER_HPP_
#define RM_INTERFACES__MSG__DETAIL__DEBUG_ARMORS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rm_interfaces/msg/detail/debug_armors__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rm_interfaces
{

namespace msg
{

namespace builder
{

class Init_DebugArmors_data
{
public:
  Init_DebugArmors_data()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::rm_interfaces::msg::DebugArmors data(::rm_interfaces::msg::DebugArmors::_data_type arg)
  {
    msg_.data = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rm_interfaces::msg::DebugArmors msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rm_interfaces::msg::DebugArmors>()
{
  return rm_interfaces::msg::builder::Init_DebugArmors_data();
}

}  // namespace rm_interfaces

#endif  // RM_INTERFACES__MSG__DETAIL__DEBUG_ARMORS__BUILDER_HPP_
