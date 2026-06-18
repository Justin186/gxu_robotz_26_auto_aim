// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from rm_interfaces:msg/Target.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__MSG__DETAIL__TARGET__TRAITS_HPP_
#define RM_INTERFACES__MSG__DETAIL__TARGET__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "rm_interfaces/msg/detail/target__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'position'
#include "geometry_msgs/msg/detail/point__traits.hpp"
// Member 'velocity'
#include "geometry_msgs/msg/detail/vector3__traits.hpp"

namespace rm_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const Target & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: tracking
  {
    out << "tracking: ";
    rosidl_generator_traits::value_to_yaml(msg.tracking, out);
    out << ", ";
  }

  // member: id
  {
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << ", ";
  }

  // member: armors_num
  {
    out << "armors_num: ";
    rosidl_generator_traits::value_to_yaml(msg.armors_num, out);
    out << ", ";
  }

  // member: position
  {
    out << "position: ";
    to_flow_style_yaml(msg.position, out);
    out << ", ";
  }

  // member: velocity
  {
    out << "velocity: ";
    to_flow_style_yaml(msg.velocity, out);
    out << ", ";
  }

  // member: yaw
  {
    out << "yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.yaw, out);
    out << ", ";
  }

  // member: v_yaw
  {
    out << "v_yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.v_yaw, out);
    out << ", ";
  }

  // member: radius_1
  {
    out << "radius_1: ";
    rosidl_generator_traits::value_to_yaml(msg.radius_1, out);
    out << ", ";
  }

  // member: radius_2
  {
    out << "radius_2: ";
    rosidl_generator_traits::value_to_yaml(msg.radius_2, out);
    out << ", ";
  }

  // member: d_za
  {
    out << "d_za: ";
    rosidl_generator_traits::value_to_yaml(msg.d_za, out);
    out << ", ";
  }

  // member: d_zc
  {
    out << "d_zc: ";
    rosidl_generator_traits::value_to_yaml(msg.d_zc, out);
    out << ", ";
  }

  // member: yaw_diff
  {
    out << "yaw_diff: ";
    rosidl_generator_traits::value_to_yaml(msg.yaw_diff, out);
    out << ", ";
  }

  // member: position_diff
  {
    out << "position_diff: ";
    rosidl_generator_traits::value_to_yaml(msg.position_diff, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Target & msg,
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

  // member: tracking
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tracking: ";
    rosidl_generator_traits::value_to_yaml(msg.tracking, out);
    out << "\n";
  }

  // member: id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << "\n";
  }

  // member: armors_num
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "armors_num: ";
    rosidl_generator_traits::value_to_yaml(msg.armors_num, out);
    out << "\n";
  }

  // member: position
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "position:\n";
    to_block_style_yaml(msg.position, out, indentation + 2);
  }

  // member: velocity
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "velocity:\n";
    to_block_style_yaml(msg.velocity, out, indentation + 2);
  }

  // member: yaw
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.yaw, out);
    out << "\n";
  }

  // member: v_yaw
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "v_yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.v_yaw, out);
    out << "\n";
  }

  // member: radius_1
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "radius_1: ";
    rosidl_generator_traits::value_to_yaml(msg.radius_1, out);
    out << "\n";
  }

  // member: radius_2
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "radius_2: ";
    rosidl_generator_traits::value_to_yaml(msg.radius_2, out);
    out << "\n";
  }

  // member: d_za
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "d_za: ";
    rosidl_generator_traits::value_to_yaml(msg.d_za, out);
    out << "\n";
  }

  // member: d_zc
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "d_zc: ";
    rosidl_generator_traits::value_to_yaml(msg.d_zc, out);
    out << "\n";
  }

  // member: yaw_diff
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "yaw_diff: ";
    rosidl_generator_traits::value_to_yaml(msg.yaw_diff, out);
    out << "\n";
  }

  // member: position_diff
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "position_diff: ";
    rosidl_generator_traits::value_to_yaml(msg.position_diff, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Target & msg, bool use_flow_style = false)
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
  const rm_interfaces::msg::Target & msg,
  std::ostream & out, size_t indentation = 0)
{
  rm_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use rm_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const rm_interfaces::msg::Target & msg)
{
  return rm_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<rm_interfaces::msg::Target>()
{
  return "rm_interfaces::msg::Target";
}

template<>
inline const char * name<rm_interfaces::msg::Target>()
{
  return "rm_interfaces/msg/Target";
}

template<>
struct has_fixed_size<rm_interfaces::msg::Target>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<rm_interfaces::msg::Target>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<rm_interfaces::msg::Target>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // RM_INTERFACES__MSG__DETAIL__TARGET__TRAITS_HPP_
