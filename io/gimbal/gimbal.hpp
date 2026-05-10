#ifndef IO__GIMBAL_HPP
#define IO__GIMBAL_HPP

#include <Eigen/Geometry>
#include <atomic>
#include <chrono>
#include <mutex>
#include <string>
#include <thread>
#include <tuple>

#include "serial/serial.h"
#include "tools/thread_safe_queue.hpp"

namespace io
{
struct __attribute__((packed)) GimbalToVision
{
  uint8_t head[2] = {'S', 'P'};
  uint8_t mode;  // 0: 空闲, 1: 自瞄, 2: 小符, 3: 大符
  float q[4];    // wxyz顺序
  float yaw;
  float yaw_vel;
  float pitch;
  float pitch_vel;
  float bullet_speed;
  uint16_t bullet_count;  // 子弹累计发送次数
  float gimbal_yaw;
  uint16_t crc16;
};

static_assert(sizeof(GimbalToVision) <= 64);

struct __attribute__((packed)) VisionToGimbal
{
  uint8_t head[2] = {'S', 'P'};
  uint8_t mode;  // 0: 不控制, 1: 控制云台但不开火，2: 控制云台且开火
  float yaw;
  float yaw_vel;
  float yaw_acc;
  float pitch;
  float pitch_vel;
  float pitch_acc;
  uint16_t crc16;
};

static_assert(sizeof(VisionToGimbal) <= 64);

struct __attribute__((packed)) NavToGimbal
{
    uint8_t head = 0xA5;
    float linear_x;
    float linear_y;
    float linear_z;
    float angular_x;
    float angular_y;
    float angular_z;
    uint8_t move_mode;
    uint16_t crc16;
};

struct __attribute__((packed)) GimbalToNav   // 从电控接收，发给导航
{
    uint8_t head[2] = {0xB5, 0xA5};   // 改为双字节
        // ---- 以下字段严格对应 STM32_to_PC ----
    uint8_t  vulnerability_buff;         // 机器人负防御增益
    uint16_t current_hp;                 // 当前血量
    uint16_t shooter_17mm_barrel_heat;   // 枪口热量
    uint16_t projectile_allowance_17mm;  // 剩余允许发弹量
    uint8_t  current_posture;            // 当前姿态 (1=进攻 2=防御 3=移动)
    uint16_t exchanged_ammo_total;       // 累计成功兑换的允许发弹量
    uint8_t  game_progress;              // 当前比赛阶段
    uint16_t stage_remain_time;          // 当前阶段剩余时间
    uint16_t outpost_Hp;                 // 前哨站血量
    uint16_t base_Hp;                    // 基地血量
    float    pos_x;                      // 位置 x (米)
    float    pos_y;                      // 位置 y (米)
    // ---- 以上字段完全来自电控新协议 ----
    uint16_t crc16;                      // CRC16 校验，保持不变
};

enum class GimbalMode
{
  IDLE,        // 空闲
  AUTO_AIM,    // 自瞄
  SMALL_BUFF,  // 小符
  BIG_BUFF     // 大符
};

struct GimbalState
{
  float yaw;
  float yaw_vel;
  float pitch;
  float pitch_vel;
  float bullet_speed;
  uint16_t bullet_count;
  uint16_t current_hp; // 哨兵当前血量
  uint8_t game_progress; // 当前比赛阶段
};

struct NavState
{
  uint8_t  vulnerability_buff;         // 机器人负防御增益
  uint16_t current_hp;                 // 当前血量
  uint16_t shooter_17mm_barrel_heat;   // 枪口热量
  uint16_t projectile_allowance_17mm;  // 剩余允许发弹量
  uint8_t  current_posture;            // 当前姿态 (1=进攻 2=防御 3=移动)
  uint16_t exchanged_ammo_total;       // 累计成功兑换的允许发弹量
  uint8_t  game_progress;              // 当前比赛阶段
  uint16_t stage_remain_time;          // 当前阶段剩余时间
  uint16_t outpost_Hp;                 // 前哨站血量
  uint16_t base_Hp;                    // 基地血量
  uint32_t enemy_outpost_status;       // 敌方前哨站状态
  float    pos_x;                      // 位置 x (米)
  float    pos_y;                      // 位置 y (米)
};

class Gimbal
{
public:
  Gimbal(const std::string & config_path);

  ~Gimbal();

  GimbalMode mode() const;
  GimbalState state() const;
  NavState nav_state() const;
  
  // 新增接口：设置视觉自瞄状态
  void set_aim_status(bool detect_enemy);
  bool is_detect_enemy() const;

  std::string str(GimbalMode mode) const;
  float yaw() const;
  Eigen::Quaterniond q(std::chrono::steady_clock::time_point t);

  void send(
    bool control, bool fire, float yaw, float yaw_vel, float yaw_acc, float pitch, float pitch_vel,
    float pitch_acc);

  void send(io::VisionToGimbal VisionToGimbal);

private:
  std::thread thread_;
  std::atomic<bool> quit_ = false;
  mutable std::mutex mutex_;

  GimbalToVision rx_data_;
  VisionToGimbal tx_data_;
  GimbalToNav rx_nav_data_;

  bool aim_detect_enemy_ = false;

  GimbalMode mode_ = GimbalMode::IDLE;
  GimbalState state_;
  NavState current_nav_state_{};
  tools::ThreadSafeQueue<std::tuple<Eigen::Quaterniond, std::chrono::steady_clock::time_point>>
    queue_{1000};

  bool read(uint8_t * buffer, size_t size);
  void read_thread();
  void reconnect();

protected:
  mutable std::mutex serial_mutex_;
  serial::Serial serial_;
};

}  // namespace io

#endif  // IO__GIMBAL_HPP
