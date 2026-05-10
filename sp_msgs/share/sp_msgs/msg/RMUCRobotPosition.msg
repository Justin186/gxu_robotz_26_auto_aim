# =============================================================================
# RMUCRobotPosition.msg — 机器人位姿与导航到达判定 (0x0203 / 定位系统)
# =============================================================================
# 话题: /robot_position        频率: 50 Hz
# 来源: 定位系统 (LiDAR SLAM)
# 订阅: 导航发我 -> RmucSubRobotPosition → 写入黑板 {pose.x} / {pose.y} / {is_at_nav_goal}
# 引用: SelectBestTarget, SelectObjective, SelectNearestDispelCard,
#       SelectNearestResupplyStation, SelectSafeRetreatGoal, IsAtGoal,
#       IsAtNavGoal, WaypointPatrol, MoveAround
# =============================================================================

std_msgs/Header header

float32 pose_x               # [4B] 位置 x (meter, map 坐标系)
float32 pose_y               # [4B] 位置 y (meter, map 坐标系)
# float32 pose_yaw             # 航向角 (radian, map 坐标系)
bool    is_at_nav_goal        # Nav2 当前无活动目标或最新目标已结束
