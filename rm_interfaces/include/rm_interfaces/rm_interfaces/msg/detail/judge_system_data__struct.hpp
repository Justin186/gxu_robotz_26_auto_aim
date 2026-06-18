// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from rm_interfaces:msg/JudgeSystemData.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__MSG__DETAIL__JUDGE_SYSTEM_DATA__STRUCT_HPP_
#define RM_INTERFACES__MSG__DETAIL__JUDGE_SYSTEM_DATA__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'operator_command'
#include "rm_interfaces/msg/detail/operator_command__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__rm_interfaces__msg__JudgeSystemData __attribute__((deprecated))
#else
# define DEPRECATED__rm_interfaces__msg__JudgeSystemData __declspec(deprecated)
#endif

namespace rm_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct JudgeSystemData_
{
  using Type = JudgeSystemData_<ContainerAllocator>;

  explicit JudgeSystemData_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : operator_command(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->game_status = 0;
      this->remaining_time = 0;
      this->blood = 0;
      this->outpost_hp = 0;
    }
  }

  explicit JudgeSystemData_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : operator_command(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->game_status = 0;
      this->remaining_time = 0;
      this->blood = 0;
      this->outpost_hp = 0;
    }
  }

  // field types and members
  using _game_status_type =
    uint8_t;
  _game_status_type game_status;
  using _remaining_time_type =
    int16_t;
  _remaining_time_type remaining_time;
  using _blood_type =
    int16_t;
  _blood_type blood;
  using _outpost_hp_type =
    int16_t;
  _outpost_hp_type outpost_hp;
  using _operator_command_type =
    rm_interfaces::msg::OperatorCommand_<ContainerAllocator>;
  _operator_command_type operator_command;

  // setters for named parameter idiom
  Type & set__game_status(
    const uint8_t & _arg)
  {
    this->game_status = _arg;
    return *this;
  }
  Type & set__remaining_time(
    const int16_t & _arg)
  {
    this->remaining_time = _arg;
    return *this;
  }
  Type & set__blood(
    const int16_t & _arg)
  {
    this->blood = _arg;
    return *this;
  }
  Type & set__outpost_hp(
    const int16_t & _arg)
  {
    this->outpost_hp = _arg;
    return *this;
  }
  Type & set__operator_command(
    const rm_interfaces::msg::OperatorCommand_<ContainerAllocator> & _arg)
  {
    this->operator_command = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    rm_interfaces::msg::JudgeSystemData_<ContainerAllocator> *;
  using ConstRawPtr =
    const rm_interfaces::msg::JudgeSystemData_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<rm_interfaces::msg::JudgeSystemData_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<rm_interfaces::msg::JudgeSystemData_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      rm_interfaces::msg::JudgeSystemData_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<rm_interfaces::msg::JudgeSystemData_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      rm_interfaces::msg::JudgeSystemData_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<rm_interfaces::msg::JudgeSystemData_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<rm_interfaces::msg::JudgeSystemData_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<rm_interfaces::msg::JudgeSystemData_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__rm_interfaces__msg__JudgeSystemData
    std::shared_ptr<rm_interfaces::msg::JudgeSystemData_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__rm_interfaces__msg__JudgeSystemData
    std::shared_ptr<rm_interfaces::msg::JudgeSystemData_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const JudgeSystemData_ & other) const
  {
    if (this->game_status != other.game_status) {
      return false;
    }
    if (this->remaining_time != other.remaining_time) {
      return false;
    }
    if (this->blood != other.blood) {
      return false;
    }
    if (this->outpost_hp != other.outpost_hp) {
      return false;
    }
    if (this->operator_command != other.operator_command) {
      return false;
    }
    return true;
  }
  bool operator!=(const JudgeSystemData_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct JudgeSystemData_

// alias to use template instance with default allocator
using JudgeSystemData =
  rm_interfaces::msg::JudgeSystemData_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace rm_interfaces

#endif  // RM_INTERFACES__MSG__DETAIL__JUDGE_SYSTEM_DATA__STRUCT_HPP_
