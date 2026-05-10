// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sp_msgs:msg/RMUCTeamHP.idl
// generated code does not contain a copyright notice

#ifndef SP_MSGS__MSG__DETAIL__RMUC_TEAM_HP__STRUCT_H_
#define SP_MSGS__MSG__DETAIL__RMUC_TEAM_HP__STRUCT_H_

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

/// Struct defined in msg/RMUCTeamHP in the package sp_msgs.
/**
  * =============================================================================
  * RMUCTeamHP.msg — 己方各机器人与建筑血量 (裁判系统 0x0003)
  * =============================================================================
  * 话题: /team_hp                  频率: 1 Hz
  * 来源: 电控/裁判系统串口解析节点
  * 订阅: RmucSubTeamHP → 写入黑板
  * 引用: ParseSentryBlackboard → 前哨站存活判断, 态势感知
  * =============================================================================
 */
typedef struct sp_msgs__msg__RMUCTeamHP
{
  std_msgs__msg__Header header;
  /// ── 己方建筑  ──
  /// [2B] offset 12: 前哨站血量 (0=被击毁)
  uint16_t outpost_hp;
  /// offset 14: 基地血量
  uint16_t base_hp;
} sp_msgs__msg__RMUCTeamHP;

// Struct for a sequence of sp_msgs__msg__RMUCTeamHP.
typedef struct sp_msgs__msg__RMUCTeamHP__Sequence
{
  sp_msgs__msg__RMUCTeamHP * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sp_msgs__msg__RMUCTeamHP__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SP_MSGS__MSG__DETAIL__RMUC_TEAM_HP__STRUCT_H_
