// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rm_interfaces:srv/RunHandEyeCalibration.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__SRV__DETAIL__RUN_HAND_EYE_CALIBRATION__BUILDER_HPP_
#define RM_INTERFACES__SRV__DETAIL__RUN_HAND_EYE_CALIBRATION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rm_interfaces/srv/detail/run_hand_eye_calibration__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rm_interfaces
{

namespace srv
{


}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::rm_interfaces::srv::RunHandEyeCalibration_Request>()
{
  return ::rm_interfaces::srv::RunHandEyeCalibration_Request(rosidl_runtime_cpp::MessageInitialization::ZERO);
}

}  // namespace rm_interfaces


namespace rm_interfaces
{

namespace srv
{

namespace builder
{

class Init_RunHandEyeCalibration_Response_yaml_path
{
public:
  explicit Init_RunHandEyeCalibration_Response_yaml_path(::rm_interfaces::srv::RunHandEyeCalibration_Response & msg)
  : msg_(msg)
  {}
  ::rm_interfaces::srv::RunHandEyeCalibration_Response yaml_path(::rm_interfaces::srv::RunHandEyeCalibration_Response::_yaml_path_type arg)
  {
    msg_.yaml_path = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rm_interfaces::srv::RunHandEyeCalibration_Response msg_;
};

class Init_RunHandEyeCalibration_Response_success
{
public:
  Init_RunHandEyeCalibration_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RunHandEyeCalibration_Response_yaml_path success(::rm_interfaces::srv::RunHandEyeCalibration_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_RunHandEyeCalibration_Response_yaml_path(msg_);
  }

private:
  ::rm_interfaces::srv::RunHandEyeCalibration_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::rm_interfaces::srv::RunHandEyeCalibration_Response>()
{
  return rm_interfaces::srv::builder::Init_RunHandEyeCalibration_Response_success();
}

}  // namespace rm_interfaces

#endif  // RM_INTERFACES__SRV__DETAIL__RUN_HAND_EYE_CALIBRATION__BUILDER_HPP_
