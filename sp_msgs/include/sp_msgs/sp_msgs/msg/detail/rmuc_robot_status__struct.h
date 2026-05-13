// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sp_msgs:msg/RMUCRobotStatus.idl
// generated code does not contain a copyright notice

#ifndef SP_MSGS__MSG__DETAIL__RMUC_ROBOT_STATUS__STRUCT_H_
#define SP_MSGS__MSG__DETAIL__RMUC_ROBOT_STATUS__STRUCT_H_

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

/// Struct defined in msg/RMUCRobotStatus in the package sp_msgs.
/**
  * =============================================================================
  * RMUCRobotStatus.msg — 机器人综合状态 (0x0201/0x0202/0x0003/0x0101/0x0105)
  * =============================================================================
  * 话题: /robot_status          频率: 10 Hz
  * 来源: 电控/裁判系统串口解析节点
  * 订阅: RmucSubRobotStatus → 写入黑板 {robot_status}
  * 引用: ParseSentryBlackboard, IsDead, IsHPBelow, DetectRespawnAndSetRecovery,
  *       WaitAndHeal, DecideRespawnCmd
  * =============================================================================
 */
typedef struct sp_msgs__msg__RMUCRobotStatus
{
  std_msgs__msg__Header header;
  /// ── 血量与射击热量 ──
  /// [2B] 当前血量
  uint16_t current_hp;
  /// 当前枪口热量
  uint16_t shooter_heat;
  /// ── 弹丸与允许发弹量 ──
  /// [2B] 剩余允许发弹量
  uint16_t ammo_allow;
  /// ── 己方建筑血量 (原 0x0003 /team_hp，现并入 robot_status) ──
  /// [2B] offset 12: 前哨站血量 (0=被击毁)
  uint16_t outpost_hp;
  /// offset 14: 基地血量
  uint16_t base_hp;
  /// ── 状态标志位 ──
  /// [1B] 敌方前哨站状态 (outpost_status)
  /// 0: 无敌
  /// 1: 存活, 解除无敌, 中部装甲旋转
  /// 2: 存活, 解除无敌, 中部装甲停转
  /// 3: 被击毁, 不可重建
  /// 4: 被击毁, 可重建
  /// 5: 被击毁, 重建中
  uint32_t enemy_outpost_status;
  /// ── 视觉检测 ──
  /// [1B] 是否检测到敌人
  bool is_detect_enemy;
} sp_msgs__msg__RMUCRobotStatus;

// Struct for a sequence of sp_msgs__msg__RMUCRobotStatus.
typedef struct sp_msgs__msg__RMUCRobotStatus__Sequence
{
  sp_msgs__msg__RMUCRobotStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sp_msgs__msg__RMUCRobotStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SP_MSGS__MSG__DETAIL__RMUC_ROBOT_STATUS__STRUCT_H_
