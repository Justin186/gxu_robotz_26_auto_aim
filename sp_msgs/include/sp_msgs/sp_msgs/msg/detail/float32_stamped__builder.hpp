// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from sp_msgs:msg/Float32Stamped.idl
// generated code does not contain a copyright notice

#ifndef SP_MSGS__MSG__DETAIL__FLOAT32_STAMPED__BUILDER_HPP_
#define SP_MSGS__MSG__DETAIL__FLOAT32_STAMPED__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "sp_msgs/msg/detail/float32_stamped__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace sp_msgs
{

namespace msg
{

namespace builder
{

class Init_Float32Stamped_data
{
public:
  explicit Init_Float32Stamped_data(::sp_msgs::msg::Float32Stamped & msg)
  : msg_(msg)
  {}
  ::sp_msgs::msg::Float32Stamped data(::sp_msgs::msg::Float32Stamped::_data_type arg)
  {
    msg_.data = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sp_msgs::msg::Float32Stamped msg_;
};

class Init_Float32Stamped_header
{
public:
  Init_Float32Stamped_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Float32Stamped_data header(::sp_msgs::msg::Float32Stamped::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_Float32Stamped_data(msg_);
  }

private:
  ::sp_msgs::msg::Float32Stamped msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::sp_msgs::msg::Float32Stamped>()
{
  return sp_msgs::msg::builder::Init_Float32Stamped_header();
}

}  // namespace sp_msgs

#endif  // SP_MSGS__MSG__DETAIL__FLOAT32_STAMPED__BUILDER_HPP_
