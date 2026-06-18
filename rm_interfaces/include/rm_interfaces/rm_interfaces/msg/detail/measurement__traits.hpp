// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from rm_interfaces:msg/Measurement.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__MSG__DETAIL__MEASUREMENT__TRAITS_HPP_
#define RM_INTERFACES__MSG__DETAIL__MEASUREMENT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "rm_interfaces/msg/detail/measurement__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace rm_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const Measurement & msg,
  std::ostream & out)
{
  out << "{";
  // member: x1
  {
    out << "x1: ";
    rosidl_generator_traits::value_to_yaml(msg.x1, out);
    out << ", ";
  }

  // member: y1
  {
    out << "y1: ";
    rosidl_generator_traits::value_to_yaml(msg.y1, out);
    out << ", ";
  }

  // member: z1
  {
    out << "z1: ";
    rosidl_generator_traits::value_to_yaml(msg.z1, out);
    out << ", ";
  }

  // member: yaw1
  {
    out << "yaw1: ";
    rosidl_generator_traits::value_to_yaml(msg.yaw1, out);
    out << ", ";
  }

  // member: x2
  {
    out << "x2: ";
    rosidl_generator_traits::value_to_yaml(msg.x2, out);
    out << ", ";
  }

  // member: y2
  {
    out << "y2: ";
    rosidl_generator_traits::value_to_yaml(msg.y2, out);
    out << ", ";
  }

  // member: z2
  {
    out << "z2: ";
    rosidl_generator_traits::value_to_yaml(msg.z2, out);
    out << ", ";
  }

  // member: yaw2
  {
    out << "yaw2: ";
    rosidl_generator_traits::value_to_yaml(msg.yaw2, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Measurement & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: x1
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x1: ";
    rosidl_generator_traits::value_to_yaml(msg.x1, out);
    out << "\n";
  }

  // member: y1
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "y1: ";
    rosidl_generator_traits::value_to_yaml(msg.y1, out);
    out << "\n";
  }

  // member: z1
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "z1: ";
    rosidl_generator_traits::value_to_yaml(msg.z1, out);
    out << "\n";
  }

  // member: yaw1
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "yaw1: ";
    rosidl_generator_traits::value_to_yaml(msg.yaw1, out);
    out << "\n";
  }

  // member: x2
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x2: ";
    rosidl_generator_traits::value_to_yaml(msg.x2, out);
    out << "\n";
  }

  // member: y2
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "y2: ";
    rosidl_generator_traits::value_to_yaml(msg.y2, out);
    out << "\n";
  }

  // member: z2
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "z2: ";
    rosidl_generator_traits::value_to_yaml(msg.z2, out);
    out << "\n";
  }

  // member: yaw2
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "yaw2: ";
    rosidl_generator_traits::value_to_yaml(msg.yaw2, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Measurement & msg, bool use_flow_style = false)
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
  const rm_interfaces::msg::Measurement & msg,
  std::ostream & out, size_t indentation = 0)
{
  rm_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use rm_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const rm_interfaces::msg::Measurement & msg)
{
  return rm_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<rm_interfaces::msg::Measurement>()
{
  return "rm_interfaces::msg::Measurement";
}

template<>
inline const char * name<rm_interfaces::msg::Measurement>()
{
  return "rm_interfaces/msg/Measurement";
}

template<>
struct has_fixed_size<rm_interfaces::msg::Measurement>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<rm_interfaces::msg::Measurement>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<rm_interfaces::msg::Measurement>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // RM_INTERFACES__MSG__DETAIL__MEASUREMENT__TRAITS_HPP_
