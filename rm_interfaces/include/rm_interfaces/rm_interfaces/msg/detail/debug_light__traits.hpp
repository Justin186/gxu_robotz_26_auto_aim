// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from rm_interfaces:msg/DebugLight.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__MSG__DETAIL__DEBUG_LIGHT__TRAITS_HPP_
#define RM_INTERFACES__MSG__DETAIL__DEBUG_LIGHT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "rm_interfaces/msg/detail/debug_light__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace rm_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const DebugLight & msg,
  std::ostream & out)
{
  out << "{";
  // member: center_x
  {
    out << "center_x: ";
    rosidl_generator_traits::value_to_yaml(msg.center_x, out);
    out << ", ";
  }

  // member: is_light
  {
    out << "is_light: ";
    rosidl_generator_traits::value_to_yaml(msg.is_light, out);
    out << ", ";
  }

  // member: ratio
  {
    out << "ratio: ";
    rosidl_generator_traits::value_to_yaml(msg.ratio, out);
    out << ", ";
  }

  // member: angle
  {
    out << "angle: ";
    rosidl_generator_traits::value_to_yaml(msg.angle, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const DebugLight & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: center_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "center_x: ";
    rosidl_generator_traits::value_to_yaml(msg.center_x, out);
    out << "\n";
  }

  // member: is_light
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "is_light: ";
    rosidl_generator_traits::value_to_yaml(msg.is_light, out);
    out << "\n";
  }

  // member: ratio
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ratio: ";
    rosidl_generator_traits::value_to_yaml(msg.ratio, out);
    out << "\n";
  }

  // member: angle
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "angle: ";
    rosidl_generator_traits::value_to_yaml(msg.angle, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const DebugLight & msg, bool use_flow_style = false)
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
  const rm_interfaces::msg::DebugLight & msg,
  std::ostream & out, size_t indentation = 0)
{
  rm_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use rm_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const rm_interfaces::msg::DebugLight & msg)
{
  return rm_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<rm_interfaces::msg::DebugLight>()
{
  return "rm_interfaces::msg::DebugLight";
}

template<>
inline const char * name<rm_interfaces::msg::DebugLight>()
{
  return "rm_interfaces/msg/DebugLight";
}

template<>
struct has_fixed_size<rm_interfaces::msg::DebugLight>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<rm_interfaces::msg::DebugLight>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<rm_interfaces::msg::DebugLight>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // RM_INTERFACES__MSG__DETAIL__DEBUG_LIGHT__TRAITS_HPP_
