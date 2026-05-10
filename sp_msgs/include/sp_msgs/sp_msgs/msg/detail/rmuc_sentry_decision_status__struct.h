// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sp_msgs:msg/RMUCSentryDecisionStatus.idl
// generated code does not contain a copyright notice

#ifndef SP_MSGS__MSG__DETAIL__RMUC_SENTRY_DECISION_STATUS__STRUCT_H_
#define SP_MSGS__MSG__DETAIL__RMUC_SENTRY_DECISION_STATUS__STRUCT_H_

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

/// Struct defined in msg/RMUCSentryDecisionStatus in the package sp_msgs.
/**
  * =============================================================================
  * RMUCSentryDecisionStatus.msg — 哨兵决策状态 (裁判系统 0x020D)
  * =============================================================================
  * 话题: /sentry_decision_status   频率: 10 Hz
  * 来源: 电控/裁判系统串口解析节点
  * 订阅: ❌ 已停用 (RmucSubSentryDecisionStatus 插件已删除，裁判反馈未被 BT 消费)
  * 引用: ❌ 无
  * =============================================================================
 */
typedef struct sp_msgs__msg__RMUCSentryDecisionStatus
{
  std_msgs__msg__Header header;
  /// ── 复活相关  ──
  /// bool   can_free_respawn         # bit19: 是否可以确认免费复活 (1=可)
  /// bool   can_instant_respawn      # [1B] bit20: 是否可以兑换立即复活 (1=可)
  /// uint16 instant_respawn_cost     # [2B] bit21-30: 兑换立即复活需要的金币数
  /// ── 姿态反馈  ──
  /// [1B] bit12-13: 当前姿态 (1=进攻 2=防御 3=移动)
  uint8_t current_posture;
  /// ── 远程兑换计数  ──
  /// uint8  remote_ammo_count        # bit11-14: 成功远程兑换允许发弹量的次数
  /// uint8  remote_heal_count        # bit15-18: 成功远程兑换血量的次数
  /// ── 允许发弹量兑换累计 ──
  /// [2B] bit0-10: 除远程兑换外，累计成功兑换的允许发弹量
  uint16_t exchanged_ammo_total;
} sp_msgs__msg__RMUCSentryDecisionStatus;

// Struct for a sequence of sp_msgs__msg__RMUCSentryDecisionStatus.
typedef struct sp_msgs__msg__RMUCSentryDecisionStatus__Sequence
{
  sp_msgs__msg__RMUCSentryDecisionStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sp_msgs__msg__RMUCSentryDecisionStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SP_MSGS__MSG__DETAIL__RMUC_SENTRY_DECISION_STATUS__STRUCT_H_
