// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rm_interfaces:msg/SerialReceiveData.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__MSG__DETAIL__SERIAL_RECEIVE_DATA__STRUCT_H_
#define RM_INTERFACES__MSG__DETAIL__SERIAL_RECEIVE_DATA__STRUCT_H_

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
// Member 'judge_system_data'
#include "rm_interfaces/msg/detail/judge_system_data__struct.h"

/// Struct defined in msg/SerialReceiveData in the package rm_interfaces.
typedef struct rm_interfaces__msg__SerialReceiveData
{
  std_msgs__msg__Header header;
  uint8_t mode;
  float bullet_speed;
  float roll;
  float yaw;
  float pitch;
  rm_interfaces__msg__JudgeSystemData judge_system_data;
} rm_interfaces__msg__SerialReceiveData;

// Struct for a sequence of rm_interfaces__msg__SerialReceiveData.
typedef struct rm_interfaces__msg__SerialReceiveData__Sequence
{
  rm_interfaces__msg__SerialReceiveData * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rm_interfaces__msg__SerialReceiveData__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RM_INTERFACES__MSG__DETAIL__SERIAL_RECEIVE_DATA__STRUCT_H_
