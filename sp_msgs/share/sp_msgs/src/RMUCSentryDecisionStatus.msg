# =============================================================================
# RMUCSentryDecisionStatus.msg — 哨兵决策状态 (裁判系统 0x020D)
# =============================================================================
# 话题: /sentry_decision_status   频率: 10 Hz
# 来源: 电控/裁判系统串口解析节点
# 订阅: ❌ 已停用 (RmucSubSentryDecisionStatus 插件已删除，裁判反馈未被 BT 消费)
# 引用: ❌ 无
# =============================================================================

std_msgs/Header header

# ── 复活相关  ──
# bool   can_free_respawn         # bit19: 是否可以确认免费复活 (1=可)
# bool   can_instant_respawn      # [1B] bit20: 是否可以兑换立即复活 (1=可)
# uint16 instant_respawn_cost     # [2B] bit21-30: 兑换立即复活需要的金币数

# ── 姿态反馈  ──
uint8  current_posture          # [1B] bit12-13: 当前姿态 (1=进攻 2=防御 3=移动)

# ── 远程兑换计数  ──
# uint8  remote_ammo_count        # bit11-14: 成功远程兑换允许发弹量的次数
# uint8  remote_heal_count        # bit15-18: 成功远程兑换血量的次数

# ── 允许发弹量兑换累计 ──
uint16 exchanged_ammo_total     # [2B] bit0-10: 除远程兑换外，累计成功兑换的允许发弹量

# # ── 能量机关 ──
# bool   can_activate_energy      # 附加状态 bit14: 己方能量机关是否可进入激活状态
