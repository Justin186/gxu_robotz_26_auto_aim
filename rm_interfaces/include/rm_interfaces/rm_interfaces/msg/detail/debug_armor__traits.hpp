// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from rm_interfaces:msg/DebugArmor.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__MSG__DETAIL__DEBUG_ARMOR__TRAITS_HPP_
#define RM_INTERFACES__MSG__DETAIL__DEBUG_ARMOR__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "rm_interfaces/msg/detail/debug_armor__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace rm_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const DebugArmor & msg,
  std::ostream & out)
{
  out << "{";
  // member: center_x
  {
    out << "center_x: ";
    rosidl_generator_traits::value_to_yaml(msg.center_x, out);
    out << ", ";
  }

  // member: type
  {
    out << "type: ";
    rosidl_generator_traits::value_to_yaml(msg.type, out);
    out << ", ";
  }

  // member: light_ratio
  {
    out << "light_ratio: ";
    rosidl_generator_traits::value_to_yaml(msg.light_ratio, out);
    out << ", ";
  }

  // member: center_distance
  {
    out << "center_distance: ";
    rosidl_generator_traits::value_to_yaml(msg.center_distance, out);
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
  const DebugArmor & msg,
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

  // member: type
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "type: ";
    rosidl_generator_traits::value_to_yaml(msg.type, out);
    out << "\n";
  }

  // member: light_ratio
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "light_ratio: ";
    rosidl_generator_traits::value_to_yaml(msg.light_ratio, out);
    out << "\n";
  }

  // member: center_distance
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "center_distance: ";
    rosidl_generator_traits::value_to_yaml(msg.center_distance, out);
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

inline std::string to_yaml(const DebugArmor & msg, bool use_flow_style = false)
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
  const rm_interfaces::msg::DebugArmor & msg,
  std::ostream & out, size_t indentation = 0)
{
  rm_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use rm_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const rm_interfaces::msg::DebugArmor & msg)
{
  return rm_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<rm_interfaces::msg::DebugArmor>()
{
  return "rm_interfaces::msg::DebugArmor";
}

template<>
inline const char * name<rm_interfaces::msg::DebugArmor>()
{
  return "rm_interfaces/msg/DebugArmor";
}

template<>
struct has_fixed_size<rm_interfaces::msg::DebugArmor>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<rm_interfaces::msg::DebugArmor>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<rm_interfaces::msg::DebugArmor>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // RM_INTERFACES__MSG__DETAIL__DEBUG_ARMOR__TRAITS_HPP_
