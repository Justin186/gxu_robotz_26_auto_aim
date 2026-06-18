// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rm_interfaces:msg/GimbalCmd.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__MSG__DETAIL__GIMBAL_CMD__STRUCT_H_
#define RM_INTERFACES__MSG__DETAIL__GIMBAL_CMD__STRUCT_H_

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

/// Struct defined in msg/GimbalCmd in the package rm_interfaces.
typedef struct rm_interfaces__msg__GimbalCmd
{
  std_msgs__msg__Header header;
  double pitch;
  double yaw;
  double yaw_diff;
  double pitch_diff;
  double distance;
  bool fire_advice;
} rm_interfaces__msg__GimbalCmd;

// Struct for a sequence of rm_interfaces__msg__GimbalCmd.
typedef struct rm_interfaces__msg__GimbalCmd__Sequence
{
  rm_interfaces__msg__GimbalCmd * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rm_interfaces__msg__GimbalCmd__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RM_INTERFACES__MSG__DETAIL__GIMBAL_CMD__STRUCT_H_
