// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from rm_interfaces:msg/GimbalCmd.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__MSG__DETAIL__GIMBAL_CMD__STRUCT_HPP_
#define RM_INTERFACES__MSG__DETAIL__GIMBAL_CMD__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__rm_interfaces__msg__GimbalCmd __attribute__((deprecated))
#else
# define DEPRECATED__rm_interfaces__msg__GimbalCmd __declspec(deprecated)
#endif

namespace rm_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct GimbalCmd_
{
  using Type = GimbalCmd_<ContainerAllocator>;

  explicit GimbalCmd_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->pitch = 0.0;
      this->yaw = 0.0;
      this->yaw_diff = 0.0;
      this->pitch_diff = 0.0;
      this->distance = 0.0;
      this->fire_advice = false;
    }
  }

  explicit GimbalCmd_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->pitch = 0.0;
      this->yaw = 0.0;
      this->yaw_diff = 0.0;
      this->pitch_diff = 0.0;
      this->distance = 0.0;
      this->fire_advice = false;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _pitch_type =
    double;
  _pitch_type pitch;
  using _yaw_type =
    double;
  _yaw_type yaw;
  using _yaw_diff_type =
    double;
  _yaw_diff_type yaw_diff;
  using _pitch_diff_type =
    double;
  _pitch_diff_type pitch_diff;
  using _distance_type =
    double;
  _distance_type distance;
  using _fire_advice_type =
    bool;
  _fire_advice_type fire_advice;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__pitch(
    const double & _arg)
  {
    this->pitch = _arg;
    return *this;
  }
  Type & set__yaw(
    const double & _arg)
  {
    this->yaw = _arg;
    return *this;
  }
  Type & set__yaw_diff(
    const double & _arg)
  {
    this->yaw_diff = _arg;
    return *this;
  }
  Type & set__pitch_diff(
    const double & _arg)
  {
    this->pitch_diff = _arg;
    return *this;
  }
  Type & set__distance(
    const double & _arg)
  {
    this->distance = _arg;
    return *this;
  }
  Type & set__fire_advice(
    const bool & _arg)
  {
    this->fire_advice = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    rm_interfaces::msg::GimbalCmd_<ContainerAllocator> *;
  using ConstRawPtr =
    const rm_interfaces::msg::GimbalCmd_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<rm_interfaces::msg::GimbalCmd_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<rm_interfaces::msg::GimbalCmd_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      rm_interfaces::msg::GimbalCmd_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<rm_interfaces::msg::GimbalCmd_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      rm_interfaces::msg::GimbalCmd_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<rm_interfaces::msg::GimbalCmd_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<rm_interfaces::msg::GimbalCmd_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<rm_interfaces::msg::GimbalCmd_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__rm_interfaces__msg__GimbalCmd
    std::shared_ptr<rm_interfaces::msg::GimbalCmd_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__rm_interfaces__msg__GimbalCmd
    std::shared_ptr<rm_interfaces::msg::GimbalCmd_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GimbalCmd_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->pitch != other.pitch) {
      return false;
    }
    if (this->yaw != other.yaw) {
      return false;
    }
    if (this->yaw_diff != other.yaw_diff) {
      return false;
    }
    if (this->pitch_diff != other.pitch_diff) {
      return false;
    }
    if (this->distance != other.distance) {
      return false;
    }
    if (this->fire_advice != other.fire_advice) {
      return false;
    }
    return true;
  }
  bool operator!=(const GimbalCmd_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GimbalCmd_

// alias to use template instance with default allocator
using GimbalCmd =
  rm_interfaces::msg::GimbalCmd_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace rm_interfaces

#endif  // RM_INTERFACES__MSG__DETAIL__GIMBAL_CMD__STRUCT_HPP_
