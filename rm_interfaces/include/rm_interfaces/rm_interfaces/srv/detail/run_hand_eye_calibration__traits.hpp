// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from rm_interfaces:srv/RunHandEyeCalibration.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__SRV__DETAIL__RUN_HAND_EYE_CALIBRATION__TRAITS_HPP_
#define RM_INTERFACES__SRV__DETAIL__RUN_HAND_EYE_CALIBRATION__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "rm_interfaces/srv/detail/run_hand_eye_calibration__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace rm_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const RunHandEyeCalibration_Request & msg,
  std::ostream & out)
{
  (void)msg;
  out << "null";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const RunHandEyeCalibration_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  (void)msg;
  (void)indentation;
  out << "null\n";
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const RunHandEyeCalibration_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace rm_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use rm_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const rm_interfaces::srv::RunHandEyeCalibration_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  rm_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use rm_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const rm_interfaces::srv::RunHandEyeCalibration_Request & msg)
{
  return rm_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<rm_interfaces::srv::RunHandEyeCalibration_Request>()
{
  return "rm_interfaces::srv::RunHandEyeCalibration_Request";
}

template<>
inline const char * name<rm_interfaces::srv::RunHandEyeCalibration_Request>()
{
  return "rm_interfaces/srv/RunHandEyeCalibration_Request";
}

template<>
struct has_fixed_size<rm_interfaces::srv::RunHandEyeCalibration_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<rm_interfaces::srv::RunHandEyeCalibration_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<rm_interfaces::srv::RunHandEyeCalibration_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rm_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const RunHandEyeCalibration_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << ", ";
  }

  // member: yaml_path
  {
    out << "yaml_path: ";
    rosidl_generator_traits::value_to_yaml(msg.yaml_path, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const RunHandEyeCalibration_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: success
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << "\n";
  }

  // member: yaml_path
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "yaml_path: ";
    rosidl_generator_traits::value_to_yaml(msg.yaml_path, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const RunHandEyeCalibration_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace rm_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use rm_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const rm_interfaces::srv::RunHandEyeCalibration_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  rm_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use rm_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const rm_interfaces::srv::RunHandEyeCalibration_Response & msg)
{
  return rm_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<rm_interfaces::srv::RunHandEyeCalibration_Response>()
{
  return "rm_interfaces::srv::RunHandEyeCalibration_Response";
}

template<>
inline const char * name<rm_interfaces::srv::RunHandEyeCalibration_Response>()
{
  return "rm_interfaces/srv/RunHandEyeCalibration_Response";
}

template<>
struct has_fixed_size<rm_interfaces::srv::RunHandEyeCalibration_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<rm_interfaces::srv::RunHandEyeCalibration_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<rm_interfaces::srv::RunHandEyeCalibration_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<rm_interfaces::srv::RunHandEyeCalibration>()
{
  return "rm_interfaces::srv::RunHandEyeCalibration";
}

template<>
inline const char * name<rm_interfaces::srv::RunHandEyeCalibration>()
{
  return "rm_interfaces/srv/RunHandEyeCalibration";
}

template<>
struct has_fixed_size<rm_interfaces::srv::RunHandEyeCalibration>
  : std::integral_constant<
    bool,
    has_fixed_size<rm_interfaces::srv::RunHandEyeCalibration_Request>::value &&
    has_fixed_size<rm_interfaces::srv::RunHandEyeCalibration_Response>::value
  >
{
};

template<>
struct has_bounded_size<rm_interfaces::srv::RunHandEyeCalibration>
  : std::integral_constant<
    bool,
    has_bounded_size<rm_interfaces::srv::RunHandEyeCalibration_Request>::value &&
    has_bounded_size<rm_interfaces::srv::RunHandEyeCalibration_Response>::value
  >
{
};

template<>
struct is_service<rm_interfaces::srv::RunHandEyeCalibration>
  : std::true_type
{
};

template<>
struct is_service_request<rm_interfaces::srv::RunHandEyeCalibration_Request>
  : std::true_type
{
};

template<>
struct is_service_response<rm_interfaces::srv::RunHandEyeCalibration_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // RM_INTERFACES__SRV__DETAIL__RUN_HAND_EYE_CALIBRATION__TRAITS_HPP_
