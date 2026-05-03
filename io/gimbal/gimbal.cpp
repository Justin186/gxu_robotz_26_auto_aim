#include "gimbal.hpp"

#include "tools/crc.hpp"
#include "tools/logger.hpp"
#include "tools/math_tools.hpp"
#include "tools/yaml.hpp"

namespace io
{
Gimbal::Gimbal(const std::string & config_path)
{
  auto yaml = tools::load(config_path);
  auto com_port = tools::read<std::string>(yaml, "com_port");
  //新增扫描相关参数
  max_scan_pitch_bottom_ = tools::read<float>(yaml, "max_scan_pitch_bottom_") * M_PI / 180.0f;
  max_scan_pitch_top_ = tools::read<float>(yaml, "max_scan_pitch_top_") * M_PI / 180.0f;
  scan_yaw_vel_ = tools::read<float>(yaml, "scan_yaw_vel_") * M_PI / 180.0f;
  scan_base_pitch_vel_ = tools::read<float>(yaml, "scan_base_pitch_vel_") * M_PI / 180.0f;
  scan_ex_vel_ = tools::read<float>(yaml, "scan_ex_vel_") * M_PI / 180.0f;



  try {
    serial_.setPort(com_port);
    serial_.open();
  } catch (const std::exception & e) {
    tools::logger()->error("[Gimbal] Failed to open serial: {}", e.what());
    exit(1);
  }

  thread_ = std::thread(&Gimbal::read_thread, this);

  queue_.pop();
  tools::logger()->info("[Gimbal] First q received.");
}

Gimbal::~Gimbal()
{
  quit_ = true;
  if (thread_.joinable()) thread_.join();
  serial_.close();
}

GimbalMode Gimbal::mode() const
{
  std::lock_guard<std::mutex> lock(mutex_);
  return mode_;
}

GimbalState Gimbal::state() const
{
  std::lock_guard<std::mutex> lock(mutex_);
  return state_;
}

NavState Gimbal::nav_state() const
{
  std::lock_guard<std::mutex> lock(mutex_);
  return current_nav_state_;
}

void Gimbal::set_aim_status(bool detect_enemy)
{
  std::lock_guard<std::mutex> lock(mutex_);
  aim_detect_enemy_ = detect_enemy;
}

bool Gimbal::is_detect_enemy() const
{
  std::lock_guard<std::mutex> lock(mutex_);
  return aim_detect_enemy_;
}

std::string Gimbal::str(GimbalMode mode) const
{
  switch (mode) {
    case GimbalMode::IDLE:
      return "IDLE";
    case GimbalMode::AUTO_AIM:
      return "AUTO_AIM";
    case GimbalMode::SMALL_BUFF:
      return "SMALL_BUFF";
    case GimbalMode::BIG_BUFF:
      return "BIG_BUFF";
    default:
      return "INVALID";
  }
}

float Gimbal::yaw() const
{
  std::lock_guard<std::mutex> lock(mutex_);
  return rx_data_.gimbal_yaw;
}

Eigen::Quaterniond Gimbal::q(std::chrono::steady_clock::time_point t)
{
  while (true) {
    auto [q_a, t_a] = queue_.pop();
    auto [q_b, t_b] = queue_.front();
    auto t_ab = tools::delta_time(t_a, t_b);
    auto t_ac = tools::delta_time(t_a, t);
    auto k = t_ac / t_ab;
    Eigen::Quaterniond q_c = q_a.slerp(k, q_b).normalized();
    if (t < t_a) return q_c;
    if (!(t_a < t && t <= t_b)) continue;

    return q_c;
  }
}

void Gimbal::send(io::VisionToGimbal VisionToGimbal)
{
  tx_data_.mode = VisionToGimbal.mode;
  tx_data_.yaw = VisionToGimbal.yaw;
  tx_data_.yaw_vel = VisionToGimbal.yaw_vel;
  tx_data_.yaw_acc = VisionToGimbal.yaw_acc;
  tx_data_.pitch = VisionToGimbal.pitch;
  tx_data_.pitch_vel = VisionToGimbal.pitch_vel;
  tx_data_.pitch_acc = VisionToGimbal.pitch_acc;
  tx_data_.crc16 = tools::get_crc16(
    reinterpret_cast<uint8_t *>(&tx_data_), sizeof(tx_data_) - sizeof(tx_data_.crc16));

  try {
    serial_.write(reinterpret_cast<uint8_t *>(&tx_data_), sizeof(tx_data_));
  } catch (const std::exception & e) {
    tools::logger()->warn("[Gimbal] Failed to write serial: {}", e.what());
  }
}

void Gimbal::send(
  bool control, bool fire, float yaw, float yaw_vel, float yaw_acc, float pitch, float pitch_vel,
  float pitch_acc)
{
  tx_data_.mode = control ? (fire ? 2 : 1) : 0;
  tx_data_.yaw = yaw;
  tx_data_.yaw_vel = yaw_vel;
  tx_data_.yaw_acc = yaw_acc;
  tx_data_.pitch = pitch;
  tx_data_.pitch_vel = pitch_vel;
  tx_data_.pitch_acc = pitch_acc;
  tx_data_.crc16 = tools::get_crc16(
    reinterpret_cast<uint8_t *>(&tx_data_), sizeof(tx_data_) - sizeof(tx_data_.crc16));

  try {
    serial_.write(reinterpret_cast<uint8_t *>(&tx_data_), sizeof(tx_data_));
  } catch (const std::exception & e) {
    tools::logger()->warn("[Gimbal] Failed to write serial: {}", e.what());
  }

}

bool Gimbal::read(uint8_t * buffer, size_t size)
{
  try {
    return serial_.read(buffer, size) == size;
  } catch (const std::exception & e) {
    // tools::logger()->warn("[Gimbal] Failed to read serial: {}", e.what());
    return false;
  }
}

void Gimbal::read_thread()
{
  tools::logger()->info("[Gimbal] read_thread started.");
  int error_count = 0;

  while (!quit_) {
    // tools::logger()->info("[Gimbal] Error count: {}", error_count);
    if (error_count > 10000) {
      error_count = 0;
      tools::logger()->warn("[Gimbal] Too many errors, attempting to reconnect...");
      reconnect();
      continue;
    }

    uint8_t head;
    if (!read(&head, 1)) {
      error_count++;
      continue;
    }

    if (head == 'S') {
      uint8_t second_byte;
      if (!read(&second_byte, 1)) {
        error_count++;
        continue;
      }
      if (second_byte != 'P') {
        continue;
      }
      rx_data_.head[0] = 'S';
      rx_data_.head[1] = 'P';
      
      auto t = std::chrono::steady_clock::now();

      if (!read(
            reinterpret_cast<uint8_t *>(&rx_data_) + 2,
            sizeof(rx_data_) - 2)) {
        error_count++;
        continue;
      }

      if (!tools::check_crc16(reinterpret_cast<uint8_t *>(&rx_data_), sizeof(rx_data_))) {
        tools::logger()->debug("[Gimbal] GimbalToVision CRC16 check failed.");
        continue;
      }

      error_count = 0;
      Eigen::Quaterniond q(rx_data_.q[0], rx_data_.q[1], rx_data_.q[2], rx_data_.q[3]);
      queue_.push({q, t});

      std::lock_guard<std::mutex> lock(mutex_);

      state_.yaw = rx_data_.yaw;
      state_.yaw_vel = rx_data_.yaw_vel;
      state_.pitch = rx_data_.pitch;
      state_.pitch_vel = rx_data_.pitch_vel;
      state_.bullet_speed = rx_data_.bullet_speed;
      state_.bullet_count = rx_data_.bullet_count;
      // tools::logger()->info("[Gimbal] receiver state data from diankong");

      switch (rx_data_.mode) {
        case 0:
          mode_ = GimbalMode::IDLE;
          break;
        case 1:
          mode_ = GimbalMode::AUTO_AIM;
          break;
        case 2:
          mode_ = GimbalMode::SMALL_BUFF;
          break;
        case 3:
          mode_ = GimbalMode::BIG_BUFF;
          break;
        default:
          mode_ = GimbalMode::IDLE;
          tools::logger()->warn("[Gimbal] Invalid mode: {}", rx_data_.mode);
          break;
      }
    }  else if (head == 0xB5) {
    // 读取第二个字节
    uint8_t second_byte;
    if (!read(&second_byte, 1)) {
        error_count++;
        continue;
    }
    // 检查是否为合法帧头 (0xB5 0xA5)
    if (second_byte != 0xA5) {
        continue;   // 不是导航帧，丢弃
    }
    // 填充双字节头
    rx_nav_data_.head[0] = head;
    rx_nav_data_.head[1] = second_byte;
    // tools::logger()->info("[Gimbal] receiver data from diankong");
    // 读取剩余数据 (总长度 - 2)
    if (!read(reinterpret_cast<uint8_t *>(&rx_nav_data_) + 2, sizeof(rx_nav_data_) - 2)) {
        error_count++;
        continue;
    }
    // CRC16 校验（注意：sizeof(rx_nav_data_) 现在包含双字节头）
    if (!tools::check_crc16(reinterpret_cast<uint8_t *>(&rx_nav_data_), sizeof(rx_nav_data_))) {
        tools::logger()->debug("[Gimbal] NavToGimbal CRC16 check failed. Should be {}",
                               tools::get_crc16(reinterpret_cast<uint8_t *>(&rx_nav_data_),
                                                sizeof(rx_nav_data_) - 2));
        continue;
    }
    error_count = 0;

    std::lock_guard<std::mutex> lock(mutex_);
    current_nav_state_.vulnerability_buff        = rx_nav_data_.vulnerability_buff;
    current_nav_state_.current_hp                = rx_nav_data_.current_hp;
    current_nav_state_.shooter_17mm_barrel_heat  = rx_nav_data_.shooter_17mm_barrel_heat;
    current_nav_state_.projectile_allowance_17mm = rx_nav_data_.projectile_allowance_17mm;
    current_nav_state_.current_posture           = rx_nav_data_.current_posture;
    current_nav_state_.exchanged_ammo_total      = rx_nav_data_.exchanged_ammo_total;
    current_nav_state_.game_progress             = rx_nav_data_.game_progress;
    current_nav_state_.stage_remain_time         = rx_nav_data_.stage_remain_time;
    current_nav_state_.outpost_Hp                = rx_nav_data_.outpost_Hp;
    current_nav_state_.base_Hp                   = rx_nav_data_.base_Hp;
    current_nav_state_.pos_x                     = rx_nav_data_.pos_x;
    current_nav_state_.pos_y                     = rx_nav_data_.pos_y;
} else {
    // Invalid header
    continue;
}
  }

  tools::logger()->info("[Gimbal] read_thread stopped.");
}

void Gimbal::reconnect()
{
  int max_retry_count = 10;
  for (int i = 0; i < max_retry_count && !quit_; ++i) {
    tools::logger()->warn("[Gimbal] Reconnecting serial, attempt {}/{}...", i + 1, max_retry_count);
    try {
      serial_.close();
      std::this_thread::sleep_for(std::chrono::seconds(1));
    } catch (...) {
    }

    try {
      serial_.open();  // 尝试重新打开
      queue_.clear();
      tools::logger()->info("[Gimbal] Reconnected serial successfully.");
      break;
    } catch (const std::exception & e) {
      tools::logger()->warn("[Gimbal] Reconnect failed: {}", e.what());
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
  }
}


//新增扫描
void Gimbal::scan(float yaw, float pitch)
{
  float pitch_vel = 0;
  float yaw_vel = scan_yaw_vel_; // 固定的yaw速度
  bool out = true;
  static float dir = 1; //扫描方向，1为向上扫描，-1为向下扫描 全局变量，于是可以循环利用。
  // 判断是否超出 Pitch 扫描范围
  if (pitch >= max_scan_pitch_top_) {
    out = true;
    dir = -1; // 超过上界，向下运动
  } else if (pitch <= max_scan_pitch_bottom_) {
    out = true;
    dir = 1; // 低于下界，向上运动
  } else {
    out = false;
  }

  // 由于上下限度不同，扫描速度也不同。没出界的时候根据当前pitch和边界的距离调整速度，越接近边界越快，远离边界越慢。出界了就按照最大速度扫描。
  float limit_angle = (pitch >= 0) ? max_scan_pitch_top_ : max_scan_pitch_bottom_;
  
  // 根据当前 Pitch 位置计算目标速度
  // 越接近边界速度越快（原有逻辑），离开边界时速度较慢
  if (out) {
    pitch_vel = dir * (scan_base_pitch_vel_ + scan_ex_vel_);
  } else {
    // 简单的抛物线速度分布，中心慢，两边快
    pitch_vel = dir * (scan_base_pitch_vel_ + scan_ex_vel_ * pow(std::abs(pitch) / limit_angle, 2));
  }

  // 将速度转换为目标角度（位置控制）
  // 假设控制周期约为 10ms (0.01s)，根据 auto_aim_debug_mpc.cpp 中的循环间隔
  const float dt = 0.01f;

  // 使用静态变量记录当前的命令角度，从而实现平滑的连续位置控制
  static float cmd_yaw = yaw;
  static float cmd_pitch = pitch;
  
  // 防止每次重新进入scan时突变，增加与当前实际角度差异的判断
  if (std::abs(yaw - cmd_yaw) > 10.0f * M_PI / 180.0f) {
    cmd_yaw = yaw;
  }
  if (std::abs(pitch - cmd_pitch) > 10.0f * M_PI / 180.0f) {
    cmd_pitch = pitch;
  }

  cmd_yaw += yaw_vel * dt;
  cmd_pitch += pitch_vel * dt;

  // 使用 tools::limit_rad 将角度限制在 (-PI, PI] 范围内
  cmd_yaw = static_cast<float>(tools::limit_rad(cmd_yaw));
  cmd_pitch = static_cast<float>(tools::limit_rad(cmd_pitch));

  // 填充发送数据
  tx_data_.mode = 1;             // 模式 1：控制云台
  tx_data_.yaw = cmd_yaw;        // 发送计算后的目标 Yaw 角度
  tx_data_.pitch = cmd_pitch;    // 发送计算后的目标 Pitch 角度

  // 前馈控制给电控，填入实际期望的速度，有助于电控前馈控制环的平滑响应
  tx_data_.yaw_vel = yaw_vel;
  tx_data_.yaw_acc = 0;
  tx_data_.pitch_vel = pitch_vel;
  tx_data_.pitch_acc = 0;

  tx_data_.crc16 = tools::get_crc16(
    reinterpret_cast<uint8_t *>(&tx_data_), sizeof(tx_data_) - sizeof(tx_data_.crc16));

  try {
    serial_.write(reinterpret_cast<uint8_t *>(&tx_data_), sizeof(tx_data_));
  } catch (const std::exception & e) {
    tools::logger()->warn("[Gimbal] Failed to write serial: {}", e.what());
  }
}

}  // namespace io
