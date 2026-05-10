# =============================================================================
# RMUCRobotStatus.msg — 机器人综合状态 (0x0201/0x0202/0x0003/0x0101/0x0105)
# =============================================================================
# 话题: /robot_status          频率: 10 Hz
# 来源: 电控/裁判系统串口解析节点
# 订阅: RmucSubRobotStatus → 写入黑板 {robot_status}
# 引用: ParseSentryBlackboard, IsDead, IsHPBelow, DetectRespawnAndSetRecovery,
#       WaitAndHeal, DecideRespawnCmd
# =============================================================================

std_msgs/Header header

# ── 血量与射击热量 ──
uint16 current_hp            # [2B] 当前血量
uint16 shooter_heat          # [2B] 当前枪口热量

# ── 弹丸与允许发弹量 ──
uint16 ammo_allow            # [2B] 剩余允许发弹量

# ── 己方建筑血量 (原 0x0003 /team_hp，现并入 robot_status) ──
uint16 outpost_hp            # [2B] offset 12: 前哨站血量 (0=被击毁)
uint16 base_hp               # [2B] offset 14: 基地血量

# ── 视觉检测 ──
bool    is_detect_enemy      # [1B] 是否检测到敌人

# ── 状态说明 ──
# 注意: is_dead 不是裁判系统协议字段，由 BT (ParseSentryBlackboard) 根据 current_hp <= 0 计算。
# 注意: 脱战状态(is_disengaged)不是裁判系统协议字段，
# 由 ParseSentryBlackboard 根据 shooter_heat 和 current_hp 变化自行计算。
# 规则: 存活状态下连续 6 秒未发射弹丸且未被扣血 = 脱战。


