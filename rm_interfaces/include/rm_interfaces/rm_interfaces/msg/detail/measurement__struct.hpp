// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from rm_interfaces:msg/Measurement.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__MSG__DETAIL__MEASUREMENT__STRUCT_HPP_
#define RM_INTERFACES__MSG__DETAIL__MEASUREMENT__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__rm_interfaces__msg__Measurement __attribute__((deprecated))
#else
# define DEPRECATED__rm_interfaces__msg__Measurement __declspec(deprecated)
#endif

namespace rm_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Measurement_
{
  using Type = Measurement_<ContainerAllocator>;

  explicit Measurement_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->x1 = 0.0;
      this->y1 = 0.0;
      this->z1 = 0.0;
      this->yaw1 = 0.0;
      this->x2 = 0.0;
      this->y2 = 0.0;
      this->z2 = 0.0;
      this->yaw2 = 0.0;
    }
  }

  explicit Measurement_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->x1 = 0.0;
      this->y1 = 0.0;
      this->z1 = 0.0;
      this->yaw1 = 0.0;
      this->x2 = 0.0;
      this->y2 = 0.0;
      this->z2 = 0.0;
      this->yaw2 = 0.0;
    }
  }

  // field types and members
  using _x1_type =
    double;
  _x1_type x1;
  using _y1_type =
    double;
  _y1_type y1;
  using _z1_type =
    double;
  _z1_type z1;
  using _yaw1_type =
    double;
  _yaw1_type yaw1;
  using _x2_type =
    double;
  _x2_type x2;
  using _y2_type =
    double;
  _y2_type y2;
  using _z2_type =
    double;
  _z2_type z2;
  using _yaw2_type =
    double;
  _yaw2_type yaw2;

  // setters for named parameter idiom
  Type & set__x1(
    const double & _arg)
  {
    this->x1 = _arg;
    return *this;
  }
  Type & set__y1(
    const double & _arg)
  {
    this->y1 = _arg;
    return *this;
  }
  Type & set__z1(
    const double & _arg)
  {
    this->z1 = _arg;
    return *this;
  }
  Type & set__yaw1(
    const double & _arg)
  {
    this->yaw1 = _arg;
    return *this;
  }
  Type & set__x2(
    const double & _arg)
  {
    this->x2 = _arg;
    return *this;
  }
  Type & set__y2(
    const double & _arg)
  {
    this->y2 = _arg;
    return *this;
  }
  Type & set__z2(
    const double & _arg)
  {
    this->z2 = _arg;
    return *this;
  }
  Type & set__yaw2(
    const double & _arg)
  {
    this->yaw2 = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    rm_interfaces::msg::Measurement_<ContainerAllocator> *;
  using ConstRawPtr =
    const rm_interfaces::msg::Measurement_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<rm_interfaces::msg::Measurement_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<rm_interfaces::msg::Measurement_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      rm_interfaces::msg::Measurement_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<rm_interfaces::msg::Measurement_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      rm_interfaces::msg::Measurement_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<rm_interfaces::msg::Measurement_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<rm_interfaces::msg::Measurement_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<rm_interfaces::msg::Measurement_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__rm_interfaces__msg__Measurement
    std::shared_ptr<rm_interfaces::msg::Measurement_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__rm_interfaces__msg__Measurement
    std::shared_ptr<rm_interfaces::msg::Measurement_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Measurement_ & other) const
  {
    if (this->x1 != other.x1) {
      return false;
    }
    if (this->y1 != other.y1) {
      return false;
    }
    if (this->z1 != other.z1) {
      return false;
    }
    if (this->yaw1 != other.yaw1) {
      return false;
    }
    if (this->x2 != other.x2) {
      return false;
    }
    if (this->y2 != other.y2) {
      return false;
    }
    if (this->z2 != other.z2) {
      return false;
    }
    if (this->yaw2 != other.yaw2) {
      return false;
    }
    return true;
  }
  bool operator!=(const Measurement_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Measurement_

// alias to use template instance with default allocator
using Measurement =
  rm_interfaces::msg::Measurement_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace rm_interfaces

#endif  // RM_INTERFACES__MSG__DETAIL__MEASUREMENT__STRUCT_HPP_
