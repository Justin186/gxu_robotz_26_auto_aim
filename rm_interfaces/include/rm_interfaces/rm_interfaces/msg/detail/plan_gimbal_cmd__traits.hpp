// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from rm_interfaces:msg/PlanGimbalCmd.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__MSG__DETAIL__PLAN_GIMBAL_CMD__TRAITS_HPP_
#define RM_INTERFACES__MSG__DETAIL__PLAN_GIMBAL_CMD__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "rm_interfaces/msg/detail/plan_gimbal_cmd__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace rm_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const PlanGimbalCmd & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: ref_yaw
  {
    out << "ref_yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.ref_yaw, out);
    out << ", ";
  }

  // member: ref_yaw_vel
  {
    out << "ref_yaw_vel: ";
    rosidl_generator_traits::value_to_yaml(msg.ref_yaw_vel, out);
    out << ", ";
  }

  // member: ref_yaw_acc
  {
    out << "ref_yaw_acc: ";
    rosidl_generator_traits::value_to_yaml(msg.ref_yaw_acc, out);
    out << ", ";
  }

  // member: ref_pitch
  {
    out << "ref_pitch: ";
    rosidl_generator_traits::value_to_yaml(msg.ref_pitch, out);
    out << ", ";
  }

  // member: ref_pitch_vel
  {
    out << "ref_pitch_vel: ";
    rosidl_generator_traits::value_to_yaml(msg.ref_pitch_vel, out);
    out << ", ";
  }

  // member: ref_pitch_acc
  {
    out << "ref_pitch_acc: ";
    rosidl_generator_traits::value_to_yaml(msg.ref_pitch_acc, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const PlanGimbalCmd & msg,
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

  // member: ref_yaw
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ref_yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.ref_yaw, out);
    out << "\n";
  }

  // member: ref_yaw_vel
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ref_yaw_vel: ";
    rosidl_generator_traits::value_to_yaml(msg.ref_yaw_vel, out);
    out << "\n";
  }

  // member: ref_yaw_acc
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ref_yaw_acc: ";
    rosidl_generator_traits::value_to_yaml(msg.ref_yaw_acc, out);
    out << "\n";
  }

  // member: ref_pitch
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ref_pitch: ";
    rosidl_generator_traits::value_to_yaml(msg.ref_pitch, out);
    out << "\n";
  }

  // member: ref_pitch_vel
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ref_pitch_vel: ";
    rosidl_generator_traits::value_to_yaml(msg.ref_pitch_vel, out);
    out << "\n";
  }

  // member: ref_pitch_acc
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ref_pitch_acc: ";
    rosidl_generator_traits::value_to_yaml(msg.ref_pitch_acc, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const PlanGimbalCmd & msg, bool use_flow_style = false)
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
  const rm_interfaces::msg::PlanGimbalCmd & msg,
  std::ostream & out, size_t indentation = 0)
{
  rm_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use rm_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const rm_interfaces::msg::PlanGimbalCmd & msg)
{
  return rm_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<rm_interfaces::msg::PlanGimbalCmd>()
{
  return "rm_interfaces::msg::PlanGimbalCmd";
}

template<>
inline const char * name<rm_interfaces::msg::PlanGimbalCmd>()
{
  return "rm_interfaces/msg/PlanGimbalCmd";
}

template<>
struct has_fixed_size<rm_interfaces::msg::PlanGimbalCmd>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Header>::value> {};

template<>
struct has_bounded_size<rm_interfaces::msg::PlanGimbalCmd>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Header>::value> {};

template<>
struct is_message<rm_interfaces::msg::PlanGimbalCmd>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // RM_INTERFACES__MSG__DETAIL__PLAN_GIMBAL_CMD__TRAITS_HPP_
