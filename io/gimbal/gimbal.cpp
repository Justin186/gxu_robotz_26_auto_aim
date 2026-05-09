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

  std::lock_guard<std::mutex> lock(serial_mutex_);
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

  std::lock_guard<std::mutex> lock(serial_mutex_);
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
    } else if (head == 0xB5) {
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
      current_nav_state_.enemy_outpost_status      = 0;
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

}  // namespace io
