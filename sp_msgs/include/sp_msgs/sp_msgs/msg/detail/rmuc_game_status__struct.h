// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sp_msgs:msg/RMUCGameStatus.idl
// generated code does not contain a copyright notice

#ifndef SP_MSGS__MSG__DETAIL__RMUC_GAME_STATUS__STRUCT_H_
#define SP_MSGS__MSG__DETAIL__RMUC_GAME_STATUS__STRUCT_H_

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

/// Struct defined in msg/RMUCGameStatus in the package sp_msgs.
/**
  * =============================================================================
  * RMUCGameStatus.msg — 比赛状态 (裁判系统 0x0001)
  * =============================================================================
  * 话题: /game_status          频率: 1 Hz
  * 来源: 电控/裁判系统串口解析节点
  * 订阅: RmucSubGameStatus → 写入黑板 {game_status}
  * 引用: IsGameTime, ParseSentryBlackboard
  * =============================================================================
 */
typedef struct sp_msgs__msg__RMUCGameStatus
{
  std_msgs__msg__Header header;
  /// 比赛阶段
  ///   0=未开始  1=准备阶段  2=自检阶段
  ///   3=5秒倒计时  4=比赛进行中  5=结算中
  uint8_t game_progress;
  /// 当前阶段剩余时间 (秒)
  uint16_t stage_remain_time;
} sp_msgs__msg__RMUCGameStatus;

// Struct for a sequence of sp_msgs__msg__RMUCGameStatus.
typedef struct sp_msgs__msg__RMUCGameStatus__Sequence
{
  sp_msgs__msg__RMUCGameStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sp_msgs__msg__RMUCGameStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SP_MSGS__MSG__DETAIL__RMUC_GAME_STATUS__STRUCT_H_
