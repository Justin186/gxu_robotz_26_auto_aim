// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from rm_interfaces:srv/RunHandEyeCalibration.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__SRV__DETAIL__RUN_HAND_EYE_CALIBRATION__STRUCT_HPP_
#define RM_INTERFACES__SRV__DETAIL__RUN_HAND_EYE_CALIBRATION__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__rm_interfaces__srv__RunHandEyeCalibration_Request __attribute__((deprecated))
#else
# define DEPRECATED__rm_interfaces__srv__RunHandEyeCalibration_Request __declspec(deprecated)
#endif

namespace rm_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct RunHandEyeCalibration_Request_
{
  using Type = RunHandEyeCalibration_Request_<ContainerAllocator>;

  explicit RunHandEyeCalibration_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->structure_needs_at_least_one_member = 0;
    }
  }

  explicit RunHandEyeCalibration_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->structure_needs_at_least_one_member = 0;
    }
  }

  // field types and members
  using _structure_needs_at_least_one_member_type =
    uint8_t;
  _structure_needs_at_least_one_member_type structure_needs_at_least_one_member;


  // constant declarations

  // pointer types
  using RawPtr =
    rm_interfaces::srv::RunHandEyeCalibration_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const rm_interfaces::srv::RunHandEyeCalibration_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<rm_interfaces::srv::RunHandEyeCalibration_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<rm_interfaces::srv::RunHandEyeCalibration_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      rm_interfaces::srv::RunHandEyeCalibration_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<rm_interfaces::srv::RunHandEyeCalibration_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      rm_interfaces::srv::RunHandEyeCalibration_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<rm_interfaces::srv::RunHandEyeCalibration_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<rm_interfaces::srv::RunHandEyeCalibration_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<rm_interfaces::srv::RunHandEyeCalibration_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__rm_interfaces__srv__RunHandEyeCalibration_Request
    std::shared_ptr<rm_interfaces::srv::RunHandEyeCalibration_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__rm_interfaces__srv__RunHandEyeCalibration_Request
    std::shared_ptr<rm_interfaces::srv::RunHandEyeCalibration_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const RunHandEyeCalibration_Request_ & other) const
  {
    if (this->structure_needs_at_least_one_member != other.structure_needs_at_least_one_member) {
      return false;
    }
    return true;
  }
  bool operator!=(const RunHandEyeCalibration_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct RunHandEyeCalibration_Request_

// alias to use template instance with default allocator
using RunHandEyeCalibration_Request =
  rm_interfaces::srv::RunHandEyeCalibration_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace rm_interfaces


#ifndef _WIN32
# define DEPRECATED__rm_interfaces__srv__RunHandEyeCalibration_Response __attribute__((deprecated))
#else
# define DEPRECATED__rm_interfaces__srv__RunHandEyeCalibration_Response __declspec(deprecated)
#endif

namespace rm_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct RunHandEyeCalibration_Response_
{
  using Type = RunHandEyeCalibration_Response_<ContainerAllocator>;

  explicit RunHandEyeCalibration_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->yaml_path = "";
    }
  }

  explicit RunHandEyeCalibration_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : yaml_path(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->yaml_path = "";
    }
  }

  // field types and members
  using _success_type =
    bool;
  _success_type success;
  using _yaml_path_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _yaml_path_type yaml_path;

  // setters for named parameter idiom
  Type & set__success(
    const bool & _arg)
  {
    this->success = _arg;
    return *this;
  }
  Type & set__yaml_path(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->yaml_path = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    rm_interfaces::srv::RunHandEyeCalibration_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const rm_interfaces::srv::RunHandEyeCalibration_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<rm_interfaces::srv::RunHandEyeCalibration_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<rm_interfaces::srv::RunHandEyeCalibration_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      rm_interfaces::srv::RunHandEyeCalibration_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<rm_interfaces::srv::RunHandEyeCalibration_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      rm_interfaces::srv::RunHandEyeCalibration_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<rm_interfaces::srv::RunHandEyeCalibration_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<rm_interfaces::srv::RunHandEyeCalibration_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<rm_interfaces::srv::RunHandEyeCalibration_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__rm_interfaces__srv__RunHandEyeCalibration_Response
    std::shared_ptr<rm_interfaces::srv::RunHandEyeCalibration_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__rm_interfaces__srv__RunHandEyeCalibration_Response
    std::shared_ptr<rm_interfaces::srv::RunHandEyeCalibration_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const RunHandEyeCalibration_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->yaml_path != other.yaml_path) {
      return false;
    }
    return true;
  }
  bool operator!=(const RunHandEyeCalibration_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct RunHandEyeCalibration_Response_

// alias to use template instance with default allocator
using RunHandEyeCalibration_Response =
  rm_interfaces::srv::RunHandEyeCalibration_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace rm_interfaces

namespace rm_interfaces
{

namespace srv
{

struct RunHandEyeCalibration
{
  using Request = rm_interfaces::srv::RunHandEyeCalibration_Request;
  using Response = rm_interfaces::srv::RunHandEyeCalibration_Response;
};

}  // namespace srv

}  // namespace rm_interfaces

#endif  // RM_INTERFACES__SRV__DETAIL__RUN_HAND_EYE_CALIBRATION__STRUCT_HPP_
