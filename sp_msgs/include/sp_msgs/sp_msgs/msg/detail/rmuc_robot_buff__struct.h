// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sp_msgs:msg/RMUCRobotBuff.idl
// generated code does not contain a copyright notice

#ifndef SP_MSGS__MSG__DETAIL__RMUC_ROBOT_BUFF__STRUCT_H_
#define SP_MSGS__MSG__DETAIL__RMUC_ROBOT_BUFF__STRUCT_H_

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

/// Struct defined in msg/RMUCRobotBuff in the package sp_msgs.
/**
  * =============================================================================
  * RMUCRobotBuff.msg — 机器人实时增益 (裁判系统 0x0204)
  * =============================================================================
  * 话题: /robot_buff               频率: 10 Hz
  * 来源: 电控/裁判系统串口解析节点
  * 订阅: RmucSubRobotBuff → 写入黑板 {robot_buff}
  * 引用: IsVulnerable → 易伤时切换防御姿态
  * =============================================================================
 */
typedef struct sp_msgs__msg__RMUCRobotBuff
{
  std_msgs__msg__Header header;
  /// ── 增益值 ──
  /// [1B] offset 4: 负防御增益/易伤% (值为30表示-30%防御)
  uint8_t vulnerability_pct;
} sp_msgs__msg__RMUCRobotBuff;

// Struct for a sequence of sp_msgs__msg__RMUCRobotBuff.
typedef struct sp_msgs__msg__RMUCRobotBuff__Sequence
{
  sp_msgs__msg__RMUCRobotBuff * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sp_msgs__msg__RMUCRobotBuff__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SP_MSGS__MSG__DETAIL__RMUC_ROBOT_BUFF__STRUCT_H_
