// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rm_interfaces:msg/Armor.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__MSG__DETAIL__ARMOR__BUILDER_HPP_
#define RM_INTERFACES__MSG__DETAIL__ARMOR__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rm_interfaces/msg/detail/armor__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rm_interfaces
{

namespace msg
{

namespace builder
{

class Init_Armor_pose
{
public:
  explicit Init_Armor_pose(::rm_interfaces::msg::Armor & msg)
  : msg_(msg)
  {}
  ::rm_interfaces::msg::Armor pose(::rm_interfaces::msg::Armor::_pose_type arg)
  {
    msg_.pose = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rm_interfaces::msg::Armor msg_;
};

class Init_Armor_distance_to_image_center
{
public:
  explicit Init_Armor_distance_to_image_center(::rm_interfaces::msg::Armor & msg)
  : msg_(msg)
  {}
  Init_Armor_pose distance_to_image_center(::rm_interfaces::msg::Armor::_distance_to_image_center_type arg)
  {
    msg_.distance_to_image_center = std::move(arg);
    return Init_Armor_pose(msg_);
  }

private:
  ::rm_interfaces::msg::Armor msg_;
};

class Init_Armor_type
{
public:
  explicit Init_Armor_type(::rm_interfaces::msg::Armor & msg)
  : msg_(msg)
  {}
  Init_Armor_distance_to_image_center type(::rm_interfaces::msg::Armor::_type_type arg)
  {
    msg_.type = std::move(arg);
    return Init_Armor_distance_to_image_center(msg_);
  }

private:
  ::rm_interfaces::msg::Armor msg_;
};

class Init_Armor_number
{
public:
  Init_Armor_number()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Armor_type number(::rm_interfaces::msg::Armor::_number_type arg)
  {
    msg_.number = std::move(arg);
    return Init_Armor_type(msg_);
  }

private:
  ::rm_interfaces::msg::Armor msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rm_interfaces::msg::Armor>()
{
  return rm_interfaces::msg::builder::Init_Armor_number();
}

}  // namespace rm_interfaces

#endif  // RM_INTERFACES__MSG__DETAIL__ARMOR__BUILDER_HPP_
