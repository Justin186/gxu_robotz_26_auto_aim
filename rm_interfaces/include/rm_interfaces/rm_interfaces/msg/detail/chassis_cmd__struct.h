// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rm_interfaces:msg/ChassisCmd.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__MSG__DETAIL__CHASSIS_CMD__STRUCT_H_
#define RM_INTERFACES__MSG__DETAIL__CHASSIS_CMD__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'twist'
#include "geometry_msgs/msg/detail/twist__struct.h"

/// Struct defined in msg/ChassisCmd in the package rm_interfaces.
typedef struct rm_interfaces__msg__ChassisCmd
{
  std_msgs__msg__Header header;
  bool is_spining;
  bool is_navigating;
  geometry_msgs__msg__Twist twist;
} rm_interfaces__msg__ChassisCmd;

// Struct for a sequence of rm_interfaces__msg__ChassisCmd.
typedef struct rm_interfaces__msg__ChassisCmd__Sequence
{
  rm_interfaces__msg__ChassisCmd * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rm_interfaces__msg__ChassisCmd__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RM_INTERFACES__MSG__DETAIL__CHASSIS_CMD__STRUCT_H_
