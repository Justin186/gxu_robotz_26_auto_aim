// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from rm_interfaces:msg/PlanGimbalCmd.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__MSG__DETAIL__PLAN_GIMBAL_CMD__STRUCT_HPP_
#define RM_INTERFACES__MSG__DETAIL__PLAN_GIMBAL_CMD__STRUCT_HPP_

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
# define DEPRECATED__rm_interfaces__msg__PlanGimbalCmd __attribute__((deprecated))
#else
# define DEPRECATED__rm_interfaces__msg__PlanGimbalCmd __declspec(deprecated)
#endif

namespace rm_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct PlanGimbalCmd_
{
  using Type = PlanGimbalCmd_<ContainerAllocator>;

  explicit PlanGimbalCmd_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->ref_yaw = 0.0f;
      this->ref_yaw_vel = 0.0f;
      this->ref_yaw_acc = 0.0f;
      this->ref_pitch = 0.0f;
      this->ref_pitch_vel = 0.0f;
      this->ref_pitch_acc = 0.0f;
    }
  }

  explicit PlanGimbalCmd_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->ref_yaw = 0.0f;
      this->ref_yaw_vel = 0.0f;
      this->ref_yaw_acc = 0.0f;
      this->ref_pitch = 0.0f;
      this->ref_pitch_vel = 0.0f;
      this->ref_pitch_acc = 0.0f;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _ref_yaw_type =
    float;
  _ref_yaw_type ref_yaw;
  using _ref_yaw_vel_type =
    float;
  _ref_yaw_vel_type ref_yaw_vel;
  using _ref_yaw_acc_type =
    float;
  _ref_yaw_acc_type ref_yaw_acc;
  using _ref_pitch_type =
    float;
  _ref_pitch_type ref_pitch;
  using _ref_pitch_vel_type =
    float;
  _ref_pitch_vel_type ref_pitch_vel;
  using _ref_pitch_acc_type =
    float;
  _ref_pitch_acc_type ref_pitch_acc;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__ref_yaw(
    const float & _arg)
  {
    this->ref_yaw = _arg;
    return *this;
  }
  Type & set__ref_yaw_vel(
    const float & _arg)
  {
    this->ref_yaw_vel = _arg;
    return *this;
  }
  Type & set__ref_yaw_acc(
    const float & _arg)
  {
    this->ref_yaw_acc = _arg;
    return *this;
  }
  Type & set__ref_pitch(
    const float & _arg)
  {
    this->ref_pitch = _arg;
    return *this;
  }
  Type & set__ref_pitch_vel(
    const float & _arg)
  {
    this->ref_pitch_vel = _arg;
    return *this;
  }
  Type & set__ref_pitch_acc(
    const float & _arg)
  {
    this->ref_pitch_acc = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    rm_interfaces::msg::PlanGimbalCmd_<ContainerAllocator> *;
  using ConstRawPtr =
    const rm_interfaces::msg::PlanGimbalCmd_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<rm_interfaces::msg::PlanGimbalCmd_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<rm_interfaces::msg::PlanGimbalCmd_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      rm_interfaces::msg::PlanGimbalCmd_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<rm_interfaces::msg::PlanGimbalCmd_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      rm_interfaces::msg::PlanGimbalCmd_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<rm_interfaces::msg::PlanGimbalCmd_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<rm_interfaces::msg::PlanGimbalCmd_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<rm_interfaces::msg::PlanGimbalCmd_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__rm_interfaces__msg__PlanGimbalCmd
    std::shared_ptr<rm_interfaces::msg::PlanGimbalCmd_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__rm_interfaces__msg__PlanGimbalCmd
    std::shared_ptr<rm_interfaces::msg::PlanGimbalCmd_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const PlanGimbalCmd_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->ref_yaw != other.ref_yaw) {
      return false;
    }
    if (this->ref_yaw_vel != other.ref_yaw_vel) {
      return false;
    }
    if (this->ref_yaw_acc != other.ref_yaw_acc) {
      return false;
    }
    if (this->ref_pitch != other.ref_pitch) {
      return false;
    }
    if (this->ref_pitch_vel != other.ref_pitch_vel) {
      return false;
    }
    if (this->ref_pitch_acc != other.ref_pitch_acc) {
      return false;
    }
    return true;
  }
  bool operator!=(const PlanGimbalCmd_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct PlanGimbalCmd_

// alias to use template instance with default allocator
using PlanGimbalCmd =
  rm_interfaces::msg::PlanGimbalCmd_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace rm_interfaces

#endif  // RM_INTERFACES__MSG__DETAIL__PLAN_GIMBAL_CMD__STRUCT_HPP_
