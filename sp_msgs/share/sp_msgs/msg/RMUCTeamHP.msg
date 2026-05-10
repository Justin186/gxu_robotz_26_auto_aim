# =============================================================================
# RMUCTeamHP.msg — 己方各机器人与建筑血量 (裁判系统 0x0003)
# =============================================================================
# 话题: /team_hp                  频率: 1 Hz
# 来源: 电控/裁判系统串口解析节点
# 订阅: RmucSubTeamHP → 写入黑板
# 引用: ParseSentryBlackboard → 前哨站存活判断, 态势感知
# =============================================================================

std_msgs/Header header

# ── 己方建筑  ──
uint16 outpost_hp              # [2B] offset 12: 前哨站血量 (0=被击毁)
uint16 base_hp                 # [2B] offset 14: 基地血量

# # ── 以下字段暂未启用 ──
# uint16 hero_hp                 # offset 0: 英雄血量
# uint16 engi_hp                 # offset 2: 工程血量
# uint16 infantry3_hp            # offset 4: 3号步兵血量
# uint16 infantry4_hp            # offset 6: 4号步兵血量
# uint16 sentry_hp               # offset 10: 哨兵血量
