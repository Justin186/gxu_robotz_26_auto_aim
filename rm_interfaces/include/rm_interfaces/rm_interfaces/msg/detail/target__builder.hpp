// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rm_interfaces:msg/Target.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__MSG__DETAIL__TARGET__BUILDER_HPP_
#define RM_INTERFACES__MSG__DETAIL__TARGET__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rm_interfaces/msg/detail/target__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rm_interfaces
{

namespace msg
{

namespace builder
{

class Init_Target_position_diff
{
public:
  explicit Init_Target_position_diff(::rm_interfaces::msg::Target & msg)
  : msg_(msg)
  {}
  ::rm_interfaces::msg::Target position_diff(::rm_interfaces::msg::Target::_position_diff_type arg)
  {
    msg_.position_diff = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rm_interfaces::msg::Target msg_;
};

class Init_Target_yaw_diff
{
public:
  explicit Init_Target_yaw_diff(::rm_interfaces::msg::Target & msg)
  : msg_(msg)
  {}
  Init_Target_position_diff yaw_diff(::rm_interfaces::msg::Target::_yaw_diff_type arg)
  {
    msg_.yaw_diff = std::move(arg);
    return Init_Target_position_diff(msg_);
  }

private:
  ::rm_interfaces::msg::Target msg_;
};

class Init_Target_d_zc
{
public:
  explicit Init_Target_d_zc(::rm_interfaces::msg::Target & msg)
  : msg_(msg)
  {}
  Init_Target_yaw_diff d_zc(::rm_interfaces::msg::Target::_d_zc_type arg)
  {
    msg_.d_zc = std::move(arg);
    return Init_Target_yaw_diff(msg_);
  }

private:
  ::rm_interfaces::msg::Target msg_;
};

class Init_Target_d_za
{
public:
  explicit Init_Target_d_za(::rm_interfaces::msg::Target & msg)
  : msg_(msg)
  {}
  Init_Target_d_zc d_za(::rm_interfaces::msg::Target::_d_za_type arg)
  {
    msg_.d_za = std::move(arg);
    return Init_Target_d_zc(msg_);
  }

private:
  ::rm_interfaces::msg::Target msg_;
};

class Init_Target_radius_2
{
public:
  explicit Init_Target_radius_2(::rm_interfaces::msg::Target & msg)
  : msg_(msg)
  {}
  Init_Target_d_za radius_2(::rm_interfaces::msg::Target::_radius_2_type arg)
  {
    msg_.radius_2 = std::move(arg);
    return Init_Target_d_za(msg_);
  }

private:
  ::rm_interfaces::msg::Target msg_;
};

class Init_Target_radius_1
{
public:
  explicit Init_Target_radius_1(::rm_interfaces::msg::Target & msg)
  : msg_(msg)
  {}
  Init_Target_radius_2 radius_1(::rm_interfaces::msg::Target::_radius_1_type arg)
  {
    msg_.radius_1 = std::move(arg);
    return Init_Target_radius_2(msg_);
  }

private:
  ::rm_interfaces::msg::Target msg_;
};

class Init_Target_v_yaw
{
public:
  explicit Init_Target_v_yaw(::rm_interfaces::msg::Target & msg)
  : msg_(msg)
  {}
  Init_Target_radius_1 v_yaw(::rm_interfaces::msg::Target::_v_yaw_type arg)
  {
    msg_.v_yaw = std::move(arg);
    return Init_Target_radius_1(msg_);
  }

private:
  ::rm_interfaces::msg::Target msg_;
};

class Init_Target_yaw
{
public:
  explicit Init_Target_yaw(::rm_interfaces::msg::Target & msg)
  : msg_(msg)
  {}
  Init_Target_v_yaw yaw(::rm_interfaces::msg::Target::_yaw_type arg)
  {
    msg_.yaw = std::move(arg);
    return Init_Target_v_yaw(msg_);
  }

private:
  ::rm_interfaces::msg::Target msg_;
};

class Init_Target_velocity
{
public:
  explicit Init_Target_velocity(::rm_interfaces::msg::Target & msg)
  : msg_(msg)
  {}
  Init_Target_yaw velocity(::rm_interfaces::msg::Target::_velocity_type arg)
  {
    msg_.velocity = std::move(arg);
    return Init_Target_yaw(msg_);
  }

private:
  ::rm_interfaces::msg::Target msg_;
};

class Init_Target_position
{
public:
  explicit Init_Target_position(::rm_interfaces::msg::Target & msg)
  : msg_(msg)
  {}
  Init_Target_velocity position(::rm_interfaces::msg::Target::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_Target_velocity(msg_);
  }

private:
  ::rm_interfaces::msg::Target msg_;
};

class Init_Target_armors_num
{
public:
  explicit Init_Target_armors_num(::rm_interfaces::msg::Target & msg)
  : msg_(msg)
  {}
  Init_Target_position armors_num(::rm_interfaces::msg::Target::_armors_num_type arg)
  {
    msg_.armors_num = std::move(arg);
    return Init_Target_position(msg_);
  }

private:
  ::rm_interfaces::msg::Target msg_;
};

class Init_Target_id
{
public:
  explicit Init_Target_id(::rm_interfaces::msg::Target & msg)
  : msg_(msg)
  {}
  Init_Target_armors_num id(::rm_interfaces::msg::Target::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_Target_armors_num(msg_);
  }

private:
  ::rm_interfaces::msg::Target msg_;
};

class Init_Target_tracking
{
public:
  explicit Init_Target_tracking(::rm_interfaces::msg::Target & msg)
  : msg_(msg)
  {}
  Init_Target_id tracking(::rm_interfaces::msg::Target::_tracking_type arg)
  {
    msg_.tracking = std::move(arg);
    return Init_Target_id(msg_);
  }

private:
  ::rm_interfaces::msg::Target msg_;
};

class Init_Target_header
{
public:
  Init_Target_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Target_tracking header(::rm_interfaces::msg::Target::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_Target_tracking(msg_);
  }

private:
  ::rm_interfaces::msg::Target msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rm_interfaces::msg::Target>()
{
  return rm_interfaces::msg::builder::Init_Target_header();
}

}  // namespace rm_interfaces

#endif  // RM_INTERFACES__MSG__DETAIL__TARGET__BUILDER_HPP_
