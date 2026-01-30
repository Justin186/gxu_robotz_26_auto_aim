// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sp_msgs:msg/RMUL.idl
// generated code does not contain a copyright notice

#ifndef SP_MSGS__MSG__DETAIL__RMUL__STRUCT_H_
#define SP_MSGS__MSG__DETAIL__RMUL__STRUCT_H_

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

/// Struct defined in msg/RMUL in the package sp_msgs.
/**
  * v1.6.1 0x0001 比赛状态数据
  * 新增：标准ROS头文件，包含时间戳（stamp）和坐标系（frame_id），用于数据时间戳对齐
 */
typedef struct sp_msgs__msg__RMUL
{
  std_msgs__msg__Header header;
  /// 当前比赛阶段
  uint8_t game_progress;
  /// 当前阶段剩余时间
  uint16_t stage_remain_time;
  /// 指令类型：1=开始导航，2=终止导航，3=原地不动，0=无操作
  int32_t cmd_type;
  /// 紧急停止（优先级最高，true=立刻停）
  bool emergency_stop;
  /// v1.6.1 0x020A 机器人RFID状态（此处仅保留我方哨兵补给区）
  bool rfid_supply_arrived;
  /// 控制区交互卡反馈
  bool rfid_control_arrived;
  /// 机器人控制命令（云台，底盘）
  /// 是否停止云台扫描
  bool stop_gimbal_scan;
  /// 是否启动底盘小陀螺
  bool chassis_spin;
  /// Robot position from referee system (cmd_id: 0x0203)
  /// Coordinate frame: map
  /// Unit: meter, radian  当前哨兵位置
  float x;
  float y;
  /// 哨兵当前血量
  uint16_t current_hp;
  /// 是否受到攻击 0->未受到攻击 1->受到攻击
  uint8_t is_attacked;
  /// 是否检测到敌人
  bool is_detect_enemy;
} sp_msgs__msg__RMUL;

// Struct for a sequence of sp_msgs__msg__RMUL.
typedef struct sp_msgs__msg__RMUL__Sequence
{
  sp_msgs__msg__RMUL * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sp_msgs__msg__RMUL__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SP_MSGS__MSG__DETAIL__RMUL__STRUCT_H_
