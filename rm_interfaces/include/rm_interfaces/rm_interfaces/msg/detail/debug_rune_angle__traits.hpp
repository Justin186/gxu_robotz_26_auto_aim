// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from rm_interfaces:msg/DebugRuneAngle.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__MSG__DETAIL__DEBUG_RUNE_ANGLE__TRAITS_HPP_
#define RM_INTERFACES__MSG__DETAIL__DEBUG_RUNE_ANGLE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "rm_interfaces/msg/detail/debug_rune_angle__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace rm_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const DebugRuneAngle & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: data
  {
    out << "data: ";
    rosidl_generator_traits::value_to_yaml(msg.data, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const DebugRuneAngle & msg,
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

  // member: data
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "data: ";
    rosidl_generator_traits::value_to_yaml(msg.data, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const DebugRuneAngle & msg, bool use_flow_style = false)
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
  const rm_interfaces::msg::DebugRuneAngle & msg,
  std::ostream & out, size_t indentation = 0)
{
  rm_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use rm_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const rm_interfaces::msg::DebugRuneAngle & msg)
{
  return rm_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<rm_interfaces::msg::DebugRuneAngle>()
{
  return "rm_interfaces::msg::DebugRuneAngle";
}

template<>
inline const char * name<rm_interfaces::msg::DebugRuneAngle>()
{
  return "rm_interfaces/msg/DebugRuneAngle";
}

template<>
struct has_fixed_size<rm_interfaces::msg::DebugRuneAngle>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Header>::value> {};

template<>
struct has_bounded_size<rm_interfaces::msg::DebugRuneAngle>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Header>::value> {};

template<>
struct is_message<rm_interfaces::msg::DebugRuneAngle>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // RM_INTERFACES__MSG__DETAIL__DEBUG_RUNE_ANGLE__TRAITS_HPP_
