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
  * =============================================================================
  * RMUL.msg — 统一裁判系统消息（合并所有 BT 节点所需的自定义接口）
  * =============================================================================
 */
typedef struct sp_msgs__msg__RMUL
{
  std_msgs__msg__Header header;
  /// ── 1. 比赛状态 (GameStatus, 0x0001) ──────────────────────────────────────────
  /// 当前比赛阶段 (0-4)
  uint8_t game_progress;
  /// 当前阶段剩余时间 (s)
  uint16_t stage_remain_time;
  /// ── 2. 机器人状态 (RobotStatus, 0x0201 / 0x0202) ─────────────────────────────
  /// 本机当前血量
  uint16_t current_hp;
  /// 是否受到攻击 (0=否, 1=是)
  uint8_t is_attacked;
  /// 枪口热量
  uint16_t shooter_heat;
  /// ── 3. RFID 状态 (RFID, 0x0209 / 0x020A) ─────────────────────────────────────
  /// 补给区交互卡反馈
  bool rfid_supply_arrived;
  /// 控制区交互卡反馈
  bool rfid_control_arrived;
  /// ── 5. 导航控制命令 (NavControlCmd) ───────────────────────────────────────────
  /// 指令类型：0=无操作(禁止导航), 1=开始导航(允许发起导航), 2=终止导航, 3=原地不动
  int32_t cmd_type;
  /// 紧急停止（优先级最高, true=立刻停）
  bool emergency_stop;
  /// ── 6. 机器人控制命令 (RobotControl) ──────────────────────────────────────────
  /// 是否停止云台扫描 (false=扫描, true=停止)
  bool stop_gimbal_scan;
  /// 是否启动底盘小陀螺 (false=不启动, true=启动)
  bool chassis_spin;
  /// ── 7. 机器人位姿 (RobotPosition, 0x0203) ────────────────────────────────────
  /// 当前位置 x (meter, map 坐标系)
  float x;
  /// 当前位置 y (meter, map 坐标系)
  float y;
  /// ── 8. 视觉检测 ──────────────────────────────────────────────────────────────
  /// 是否检测到敌人
  bool is_detect_enemy;
  /// ── 9. 判断机器人是否到达导航指定位置 ─────────────────────────────────────
  /// 是否到达导航目标点
  bool is_at_nav_goal;
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
