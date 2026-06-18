// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rm_interfaces:msg/JudgeSystemData.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__MSG__DETAIL__JUDGE_SYSTEM_DATA__STRUCT_H_
#define RM_INTERFACES__MSG__DETAIL__JUDGE_SYSTEM_DATA__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'operator_command'
#include "rm_interfaces/msg/detail/operator_command__struct.h"

/// Struct defined in msg/JudgeSystemData in the package rm_interfaces.
typedef struct rm_interfaces__msg__JudgeSystemData
{
  uint8_t game_status;
  int16_t remaining_time;
  int16_t blood;
  int16_t outpost_hp;
  rm_interfaces__msg__OperatorCommand operator_command;
} rm_interfaces__msg__JudgeSystemData;

// Struct for a sequence of rm_interfaces__msg__JudgeSystemData.
typedef struct rm_interfaces__msg__JudgeSystemData__Sequence
{
  rm_interfaces__msg__JudgeSystemData * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rm_interfaces__msg__JudgeSystemData__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RM_INTERFACES__MSG__DETAIL__JUDGE_SYSTEM_DATA__STRUCT_H_
