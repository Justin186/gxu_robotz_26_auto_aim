// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sp_msgs:msg/RMUCRobotControl.idl
// generated code does not contain a copyright notice

#ifndef SP_MSGS__MSG__DETAIL__RMUC_ROBOT_CONTROL__STRUCT_H_
#define SP_MSGS__MSG__DETAIL__RMUC_ROBOT_CONTROL__STRUCT_H_

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

/// Struct defined in msg/RMUCRobotControl in the package sp_msgs.
/**
  * =============================================================================
  * RMUCRobotControl.msg — 机器人控制命令
  * =============================================================================
  * 话题: /robot_control         频率: 10 Hz
  * 方向: BT → 电控
  * 发布: RmucRobotControl (各战术子树)
  * =============================================================================
 */
typedef struct sp_msgs__msg__RMUCRobotControl
{
  std_msgs__msg__Header header;
  /// 停止云台扫描
  bool stop_gimbal_scan;
  /// 底盘小陀螺旋转
  bool chassis_spin;
} sp_msgs__msg__RMUCRobotControl;

// Struct for a sequence of sp_msgs__msg__RMUCRobotControl.
typedef struct sp_msgs__msg__RMUCRobotControl__Sequence
{
  sp_msgs__msg__RMUCRobotControl * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sp_msgs__msg__RMUCRobotControl__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SP_MSGS__MSG__DETAIL__RMUC_ROBOT_CONTROL__STRUCT_H_
