// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sp_msgs:msg/RMUCSentryCmd.idl
// generated code does not contain a copyright notice

#ifndef SP_MSGS__MSG__DETAIL__RMUC_SENTRY_CMD__STRUCT_H_
#define SP_MSGS__MSG__DETAIL__RMUC_SENTRY_CMD__STRUCT_H_

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

/// Struct defined in msg/RMUCSentryCmd in the package sp_msgs.
/**
  * =============================================================================
  * RMUCSentryCmd.msg — 哨兵自主决策指令 (裁判系统 0x0120)
  * =============================================================================
  * 话题: /sentry_cmd            频率: 2 Hz
  * 方向: BT → 电控
  * 发布: SentryCmdMux (CommandHub 子树)
  * =============================================================================
 */
typedef struct sp_msgs__msg__RMUCSentryCmd
{
  std_msgs__msg__Header header;
  /// 姿态 (1=进攻 2=防御 3=移动)
  uint8_t cmd_posture;
  /// 确认复活
  bool cmd_confirm_respawn;
} sp_msgs__msg__RMUCSentryCmd;

// Struct for a sequence of sp_msgs__msg__RMUCSentryCmd.
typedef struct sp_msgs__msg__RMUCSentryCmd__Sequence
{
  sp_msgs__msg__RMUCSentryCmd * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sp_msgs__msg__RMUCSentryCmd__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SP_MSGS__MSG__DETAIL__RMUC_SENTRY_CMD__STRUCT_H_
