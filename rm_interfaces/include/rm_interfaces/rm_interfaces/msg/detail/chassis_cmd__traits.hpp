// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from rm_interfaces:msg/ChassisCmd.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__MSG__DETAIL__CHASSIS_CMD__TRAITS_HPP_
#define RM_INTERFACES__MSG__DETAIL__CHASSIS_CMD__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "rm_interfaces/msg/detail/chassis_cmd__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'twist'
#include "geometry_msgs/msg/detail/twist__traits.hpp"

namespace rm_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const ChassisCmd & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: is_spining
  {
    out << "is_spining: ";
    rosidl_generator_traits::value_to_yaml(msg.is_spining, out);
    out << ", ";
  }

  // member: is_navigating
  {
    out << "is_navigating: ";
    rosidl_generator_traits::value_to_yaml(msg.is_navigating, out);
    out << ", ";
  }

  // member: twist
  {
    out << "twist: ";
    to_flow_style_yaml(msg.twist, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ChassisCmd & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: is_spining
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "is_spining: ";
    rosidl_generator_traits::value_to_yaml(msg.is_spining, out);
    out << "\n";
  }

  // member: is_navigating
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "is_navigating: ";
    rosidl_generator_traits::value_to_yaml(msg.is_navigating, out);
    out << "\n";
  }

  // member: twist
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "twist:\n";
    to_block_style_yaml(msg.twist, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ChassisCmd & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace rm_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use rm_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const rm_interfaces::msg::ChassisCmd & msg,
  std::ostream & out, size_t indentation = 0)
{
  rm_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use rm_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const rm_interfaces::msg::ChassisCmd & msg)
{
  return rm_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<rm_interfaces::msg::ChassisCmd>()
{
  return "rm_interfaces::msg::ChassisCmd";
}

template<>
inline const char * name<rm_interfaces::msg::ChassisCmd>()
{
  return "rm_interfaces/msg/ChassisCmd";
}

template<>
struct has_fixed_size<rm_interfaces::msg::ChassisCmd>
  : std::integral_constant<bool, has_fixed_size<geometry_msgs::msg::Twist>::value && has_fixed_size<std_msgs::msg::Header>::value> {};

template<>
struct has_bounded_size<rm_interfaces::msg::ChassisCmd>
  : std::integral_constant<bool, has_bounded_size<geometry_msgs::msg::Twist>::value && has_bounded_size<std_msgs::msg::Header>::value> {};

template<>
struct is_message<rm_interfaces::msg::ChassisCmd>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // RM_INTERFACES__MSG__DETAIL__CHASSIS_CMD__TRAITS_HPP_
