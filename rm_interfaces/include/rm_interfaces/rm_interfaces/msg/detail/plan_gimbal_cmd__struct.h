// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rm_interfaces:msg/PlanGimbalCmd.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__MSG__DETAIL__PLAN_GIMBAL_CMD__STRUCT_H_
#define RM_INTERFACES__MSG__DETAIL__PLAN_GIMBAL_CMD__STRUCT_H_

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

/// Struct defined in msg/PlanGimbalCmd in the package rm_interfaces.
typedef struct rm_interfaces__msg__PlanGimbalCmd
{
  std_msgs__msg__Header header;
  float ref_yaw;
  float ref_yaw_vel;
  float ref_yaw_acc;
  float ref_pitch;
  float ref_pitch_vel;
  float ref_pitch_acc;
} rm_interfaces__msg__PlanGimbalCmd;

// Struct for a sequence of rm_interfaces__msg__PlanGimbalCmd.
typedef struct rm_interfaces__msg__PlanGimbalCmd__Sequence
{
  rm_interfaces__msg__PlanGimbalCmd * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rm_interfaces__msg__PlanGimbalCmd__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RM_INTERFACES__MSG__DETAIL__PLAN_GIMBAL_CMD__STRUCT_H_
