// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sp_msgs:msg/RMUCNavControlCmd.idl
// generated code does not contain a copyright notice

#ifndef SP_MSGS__MSG__DETAIL__RMUC_NAV_CONTROL_CMD__STRUCT_H_
#define SP_MSGS__MSG__DETAIL__RMUC_NAV_CONTROL_CMD__STRUCT_H_

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

/// Struct defined in msg/RMUCNavControlCmd in the package sp_msgs.
/**
  * =============================================================================
  * RMUCNavControlCmd.msg — 导航控制命令
  * =============================================================================
  * 话题: /nav_control_cmd       频率: 按需
  * 方向: BT → 电控
  * 发布: RmucNavControlCmd (RespawnRecovery 子树)
  * =============================================================================
 */
typedef struct sp_msgs__msg__RMUCNavControlCmd
{
  std_msgs__msg__Header header;
  /// 导航控制指令: 0=无操作 1=开始导航 2=终止导航 3=原地不动
  int32_t cmd_type;
} sp_msgs__msg__RMUCNavControlCmd;

// Struct for a sequence of sp_msgs__msg__RMUCNavControlCmd.
typedef struct sp_msgs__msg__RMUCNavControlCmd__Sequence
{
  sp_msgs__msg__RMUCNavControlCmd * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sp_msgs__msg__RMUCNavControlCmd__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SP_MSGS__MSG__DETAIL__RMUC_NAV_CONTROL_CMD__STRUCT_H_
