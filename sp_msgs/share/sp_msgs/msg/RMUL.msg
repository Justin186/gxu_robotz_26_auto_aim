# v1.6.1 0x0001 比赛状态数据
# 新增：标准ROS头文件，包含时间戳（stamp）和坐标系（frame_id），用于数据时间戳对齐
std_msgs/Header header

uint8 game_progress # 当前比赛阶段
uint16 stage_remain_time # 当前阶段剩余时间

int32 cmd_type  # 指令类型：1=开始导航，2=终止导航，3=原地不动，0=无操作
bool emergency_stop  # 紧急停止（优先级最高，true=立刻停）

# v1.6.1 0x020A 机器人RFID状态（此处仅保留我方哨兵补给区）
bool rfid_supply_arrived
# 控制区交互卡反馈
bool rfid_control_arrived

# 机器人控制命令（云台，底盘）
bool stop_gimbal_scan # 是否停止云台扫描 
bool chassis_spin # 是否启动底盘小陀螺 

# Robot position from referee system (cmd_id: 0x0203)
# Coordinate frame: map
# Unit: meter, radian  当前哨兵位置
float32 x
float32 y

uint16 current_hp # 哨兵当前血量
uint8 is_attacked # 是否受到攻击 0->未受到攻击 1->受到攻击

# 是否检测到敌人 
bool is_detect_enemy
