// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rm_interfaces:srv/SetMode.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__SRV__DETAIL__SET_MODE__BUILDER_HPP_
#define RM_INTERFACES__SRV__DETAIL__SET_MODE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rm_interfaces/srv/detail/set_mode__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rm_interfaces
{

namespace srv
{

namespace builder
{

class Init_SetMode_Request_mode
{
public:
  Init_SetMode_Request_mode()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::rm_interfaces::srv::SetMode_Request mode(::rm_interfaces::srv::SetMode_Request::_mode_type arg)
  {
    msg_.mode = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rm_interfaces::srv::SetMode_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::rm_interfaces::srv::SetMode_Request>()
{
  return rm_interfaces::srv::builder::Init_SetMode_Request_mode();
}

}  // namespace rm_interfaces


namespace rm_interfaces
{

namespace srv
{

namespace builder
{

class Init_SetMode_Response_message
{
public:
  explicit Init_SetMode_Response_message(::rm_interfaces::srv::SetMode_Response & msg)
  : msg_(msg)
  {}
  ::rm_interfaces::srv::SetMode_Response message(::rm_interfaces::srv::SetMode_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rm_interfaces::srv::SetMode_Response msg_;
};

class Init_SetMode_Response_success
{
public:
  Init_SetMode_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetMode_Response_message success(::rm_interfaces::srv::SetMode_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_SetMode_Response_message(msg_);
  }

private:
  ::rm_interfaces::srv::SetMode_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::rm_interfaces::srv::SetMode_Response>()
{
  return rm_interfaces::srv::builder::Init_SetMode_Response_success();
}

}  // namespace rm_interfaces

#endif  // RM_INTERFACES__SRV__DETAIL__SET_MODE__BUILDER_HPP_
