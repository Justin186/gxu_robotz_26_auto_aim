// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rm_interfaces:msg/OperatorCommand.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__MSG__DETAIL__OPERATOR_COMMAND__STRUCT_H_
#define RM_INTERFACES__MSG__DETAIL__OPERATOR_COMMAND__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/OperatorCommand in the package rm_interfaces.
typedef struct rm_interfaces__msg__OperatorCommand
{
  uint8_t is_retreating;
  uint8_t is_drone_avoiding;
  uint8_t is_outpost_attacking;
} rm_interfaces__msg__OperatorCommand;

// Struct for a sequence of rm_interfaces__msg__OperatorCommand.
typedef struct rm_interfaces__msg__OperatorCommand__Sequence
{
  rm_interfaces__msg__OperatorCommand * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rm_interfaces__msg__OperatorCommand__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RM_INTERFACES__MSG__DETAIL__OPERATOR_COMMAND__STRUCT_H_
