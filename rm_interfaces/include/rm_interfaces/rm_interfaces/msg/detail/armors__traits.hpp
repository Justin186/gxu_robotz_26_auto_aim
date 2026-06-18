// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from rm_interfaces:msg/Armors.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__MSG__DETAIL__ARMORS__TRAITS_HPP_
#define RM_INTERFACES__MSG__DETAIL__ARMORS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "rm_interfaces/msg/detail/armors__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'armors'
#include "rm_interfaces/msg/detail/armor__traits.hpp"

namespace rm_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const Armors & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: armors
  {
    if (msg.armors.size() == 0) {
      out << "armors: []";
    } else {
      out << "armors: [";
      size_t pending_items = msg.armors.size();
      for (auto item : msg.armors) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Armors & msg,
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

  // member: armors
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.armors.size() == 0) {
      out << "armors: []\n";
    } else {
      out << "armors:\n";
      for (auto item : msg.armors) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Armors & msg, bool use_flow_style = false)
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
  const rm_interfaces::msg::Armors & msg,
  std::ostream & out, size_t indentation = 0)
{
  rm_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use rm_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const rm_interfaces::msg::Armors & msg)
{
  return rm_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<rm_interfaces::msg::Armors>()
{
  return "rm_interfaces::msg::Armors";
}

template<>
inline const char * name<rm_interfaces::msg::Armors>()
{
  return "rm_interfaces/msg/Armors";
}

template<>
struct has_fixed_size<rm_interfaces::msg::Armors>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<rm_interfaces::msg::Armors>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<rm_interfaces::msg::Armors>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // RM_INTERFACES__MSG__DETAIL__ARMORS__TRAITS_HPP_
