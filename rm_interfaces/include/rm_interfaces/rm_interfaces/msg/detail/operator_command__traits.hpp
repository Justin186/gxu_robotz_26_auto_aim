// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from rm_interfaces:msg/OperatorCommand.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__MSG__DETAIL__OPERATOR_COMMAND__TRAITS_HPP_
#define RM_INTERFACES__MSG__DETAIL__OPERATOR_COMMAND__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "rm_interfaces/msg/detail/operator_command__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace rm_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const OperatorCommand & msg,
  std::ostream & out)
{
  out << "{";
  // member: is_retreating
  {
    out << "is_retreating: ";
    rosidl_generator_traits::value_to_yaml(msg.is_retreating, out);
    out << ", ";
  }

  // member: is_drone_avoiding
  {
    out << "is_drone_avoiding: ";
    rosidl_generator_traits::value_to_yaml(msg.is_drone_avoiding, out);
    out << ", ";
  }

  // member: is_outpost_attacking
  {
    out << "is_outpost_attacking: ";
    rosidl_generator_traits::value_to_yaml(msg.is_outpost_attacking, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const OperatorCommand & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: is_retreating
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "is_retreating: ";
    rosidl_generator_traits::value_to_yaml(msg.is_retreating, out);
    out << "\n";
  }

  // member: is_drone_avoiding
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "is_drone_avoiding: ";
    rosidl_generator_traits::value_to_yaml(msg.is_drone_avoiding, out);
    out << "\n";
  }

  // member: is_outpost_attacking
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "is_outpost_attacking: ";
    rosidl_generator_traits::value_to_yaml(msg.is_outpost_attacking, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const OperatorCommand & msg, bool use_flow_style = false)
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
  const rm_interfaces::msg::OperatorCommand & msg,
  std::ostream & out, size_t indentation = 0)
{
  rm_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use rm_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const rm_interfaces::msg::OperatorCommand & msg)
{
  return rm_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<rm_interfaces::msg::OperatorCommand>()
{
  return "rm_interfaces::msg::OperatorCommand";
}

template<>
inline const char * name<rm_interfaces::msg::OperatorCommand>()
{
  return "rm_interfaces/msg/OperatorCommand";
}

template<>
struct has_fixed_size<rm_interfaces::msg::OperatorCommand>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<rm_interfaces::msg::OperatorCommand>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<rm_interfaces::msg::OperatorCommand>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // RM_INTERFACES__MSG__DETAIL__OPERATOR_COMMAND__TRAITS_HPP_
