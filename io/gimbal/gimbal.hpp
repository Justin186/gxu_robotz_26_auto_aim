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
  uint8_t game_progress; // 当前比赛阶段
  uint16_t current_hp; // 哨兵当前血量
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
    uint16_t crc16;
};

struct __attribute__((packed)) GimbalToNav
{
    uint8_t head = 0x5A;
    uint8_t game_progress; // 当前比赛阶段
    uint16_t stage_remain_time; // 当前阶段剩余时间
    uint8_t rfid_supply_arrived; // 我方哨兵补给区
    uint8_t rfid_control_arrived; // 控制区交互卡反馈
    uint16_t current_hp; // 哨兵当前血量
    uint8_t is_attacked; // 是否受到攻击 0->未受到攻击 1->受到攻击
    float gimbal_yaw; // 云台与底盘的相对角度
    uint16_t crc16;
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

class Gimbal
{
public:
  Gimbal(const std::string & config_path);

  ~Gimbal();

  GimbalMode mode() const;
  GimbalState state() const;
  GimbalToNav nav_state() const;
  
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

  //新增扫描相关
  void scan(float yaw, float pitch);

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
  tools::ThreadSafeQueue<std::tuple<Eigen::Quaterniond, std::chrono::steady_clock::time_point>>
    queue_{1000};

  bool read(uint8_t * buffer, size_t size);
  void read_thread();
  void reconnect();
  //新增扫描相关参数
  float max_scan_pitch_bottom_;
  float max_scan_pitch_top_;
  float scan_yaw_vel_;
  float scan_base_pitch_vel_;
  float scan_ex_vel_;

protected:
  mutable std::mutex serial_mutex_;
  serial::Serial serial_;
};

}  // namespace io

#endif  // IO__GIMBAL_HPP
