// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sp_msgs:msg/RMUCEnemyTracks.idl
// generated code does not contain a copyright notice

#ifndef SP_MSGS__MSG__DETAIL__RMUC_ENEMY_TRACKS__STRUCT_H_
#define SP_MSGS__MSG__DETAIL__RMUC_ENEMY_TRACKS__STRUCT_H_

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
// Member 'enemy_x'
// Member 'enemy_y'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/RMUCEnemyTracks in the package sp_msgs.
/**
  * =============================================================================
  * RMUCEnemyTracks.msg — 雷达敌方目标跟踪
  * =============================================================================
  * 话题: /radar/enemy_tracks    频率: 10-30 Hz
  * 来源: 雷达站通信节点
  * 订阅: SubRadarTracks → 写入黑板 {radar_tracks}
  * 引用: ParseSentryBlackboard, SelectBestTarget
  * =============================================================================
 */
typedef struct sp_msgs__msg__RMUCEnemyTracks
{
  std_msgs__msg__Header header;
  /// 敌方位置 x (meter, map 坐标系)
  rosidl_runtime_c__float__Sequence enemy_x;
  /// 敌方位置 y (meter, map 坐标系)
  rosidl_runtime_c__float__Sequence enemy_y;
} sp_msgs__msg__RMUCEnemyTracks;

// Struct for a sequence of sp_msgs__msg__RMUCEnemyTracks.
typedef struct sp_msgs__msg__RMUCEnemyTracks__Sequence
{
  sp_msgs__msg__RMUCEnemyTracks * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sp_msgs__msg__RMUCEnemyTracks__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SP_MSGS__MSG__DETAIL__RMUC_ENEMY_TRACKS__STRUCT_H_
