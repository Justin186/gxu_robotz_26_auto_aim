# =============================================================================
# RMUCEnemyTracks.msg — 雷达敌方目标跟踪
# =============================================================================
# 话题: /radar/enemy_tracks    频率: 10-30 Hz
# 来源: 雷达站通信节点
# 订阅: SubRadarTracks → 写入黑板 {radar_tracks}
# 引用: ParseSentryBlackboard, SelectBestTarget
# =============================================================================

std_msgs/Header header

float32[] enemy_x            # [4B×N] 敌方位置 x (meter, map 坐标系)
float32[] enemy_y            # [4B×N] 敌方位置 y (meter, map 坐标系)

# # ── 以下字段暂未启用 ──
# uint8[]   enemy_robot_id     # 敌方机器人 ID
# float32[] enemy_confidence   # 跟踪置信度 [0.0, 1.0]
