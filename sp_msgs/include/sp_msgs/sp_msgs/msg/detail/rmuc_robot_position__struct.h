// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sp_msgs:msg/RMUCRobotPosition.idl
// generated code does not contain a copyright notice

#ifndef SP_MSGS__MSG__DETAIL__RMUC_ROBOT_POSITION__STRUCT_H_
#define SP_MSGS__MSG__DETAIL__RMUC_ROBOT_POSITION__STRUCT_H_

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

/// Struct defined in msg/RMUCRobotPosition in the package sp_msgs.
/**
  * =============================================================================
  * RMUCRobotPosition.msg — 机器人位姿与导航到达判定 (0x0203 / 定位系统)
  * =============================================================================
  * 话题: /robot_position        频率: 50 Hz
  * 来源: 定位系统 (LiDAR SLAM)
  * 订阅: 导航发我 -> RmucSubRobotPosition → 写入黑板 {pose.x} / {pose.y} / {is_at_nav_goal}
  * 引用: SelectBestTarget, SelectObjective, SelectNearestDispelCard,
  *       SelectNearestResupplyStation, SelectSafeRetreatGoal, IsAtGoal,
  *       IsAtNavGoal, WaypointPatrol, MoveAround
  * =============================================================================
 */
typedef struct sp_msgs__msg__RMUCRobotPosition
{
  std_msgs__msg__Header header;
  /// 位置 x (meter, map 坐标系)
  float pose_x;
  /// 位置 y (meter, map 坐标系)
  float pose_y;
  /// float32 pose_yaw             # 航向角 (radian, map 坐标系)
  /// Nav2 当前无活动目标或最新目标已结束
  bool is_at_nav_goal;
} sp_msgs__msg__RMUCRobotPosition;

// Struct for a sequence of sp_msgs__msg__RMUCRobotPosition.
typedef struct sp_msgs__msg__RMUCRobotPosition__Sequence
{
  sp_msgs__msg__RMUCRobotPosition * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sp_msgs__msg__RMUCRobotPosition__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SP_MSGS__MSG__DETAIL__RMUC_ROBOT_POSITION__STRUCT_H_
