// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sp_msgs:msg/Float32Stamped.idl
// generated code does not contain a copyright notice

#ifndef SP_MSGS__MSG__DETAIL__FLOAT32_STAMPED__STRUCT_H_
#define SP_MSGS__MSG__DETAIL__FLOAT32_STAMPED__STRUCT_H_

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

/// Struct defined in msg/Float32Stamped in the package sp_msgs.
typedef struct sp_msgs__msg__Float32Stamped
{
  std_msgs__msg__Header header;
  float data;
} sp_msgs__msg__Float32Stamped;

// Struct for a sequence of sp_msgs__msg__Float32Stamped.
typedef struct sp_msgs__msg__Float32Stamped__Sequence
{
  sp_msgs__msg__Float32Stamped * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sp_msgs__msg__Float32Stamped__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SP_MSGS__MSG__DETAIL__FLOAT32_STAMPED__STRUCT_H_
