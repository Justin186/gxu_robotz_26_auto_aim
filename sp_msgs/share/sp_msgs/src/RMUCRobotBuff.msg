# =============================================================================
# RMUCRobotBuff.msg — 机器人实时增益 (裁判系统 0x0204)
# =============================================================================
# 话题: /robot_buff               频率: 10 Hz
# 来源: 电控/裁判系统串口解析节点
# 订阅: RmucSubRobotBuff → 写入黑板 {robot_buff}
# 引用: IsVulnerable → 易伤时切换防御姿态
# =============================================================================

std_msgs/Header header

# ── 增益值 ──
uint8  vulnerability_pct        # [1B] offset 4: 负防御增益/易伤% (值为30表示-30%防御)

# # ── 以下字段暂未启用 ──
# uint8  heal_rate                # offset 0: 回血增益% (值为10表示每秒恢复上限血量的10%)
# uint16 cool_value               # offset 1: 射击热量冷却增益具体值 (直接加值, x/s)
# uint8  defense_pct              # offset 3: 防御增益% (值为50表示50%防御增益)
# uint16 attack_pct               # offset 5: 攻击增益% (值为50表示50%攻击增益)
# uint8  remaining_energy         # offset 7: 剩余能量值反馈 (位标识)
