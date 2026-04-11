#include "gimbal.hpp"

#include <cstring>
#include "tools/crc.hpp"
#include "tools/logger.hpp"
#include "tools/math_tools.hpp"
#include "tools/yaml.hpp"

namespace io
{
Gimbal::Gimbal(const std::string & config_path)
{
  auto yaml = tools::load(config_path);
  // 使用16进制读取 vid, pid, ep_in, ep_out 等参数
  vid_ = tools::read<uint16_t>(yaml, "vid", 0x0483);
  pid_ = tools::read<uint16_t>(yaml, "pid", 0x5740);
  ep_in_ = tools::read<uint8_t>(yaml, "ep_in", 0x81);
  ep_out_ = tools::read<uint8_t>(yaml, "ep_out", 0x01);
  interface_num_ = tools::read<int>(yaml, "interface", 0);

  if (libusb_init(&ctx_) < 0) {
    tools::logger()->error("[Gimbal] Failed to init libusb.");
    exit(1);
  }

  handle_ = libusb_open_device_with_vid_pid(ctx_, vid_, pid_);
  if (!handle_) {
    tools::logger()->error("[Gimbal] Failed to open USB device ({:04x}:{:04x}).", vid_, pid_);
    exit(1);
  }

  if (libusb_kernel_driver_active(handle_, interface_num_) == 1) {
    libusb_detach_kernel_driver(handle_, interface_num_);
  }

  if (libusb_claim_interface(handle_, interface_num_) < 0) {
    tools::logger()->error("[Gimbal] Failed to claim interface.");
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
  if (handle_) {
    libusb_release_interface(handle_, interface_num_);
    libusb_close(handle_);
  }
  if (ctx_) {
    libusb_exit(ctx_);
  }
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

  int sent = 0;
  if (!handle_ || libusb_bulk_transfer(handle_, ep_out_, reinterpret_cast<uint8_t *>(&tx_data_), sizeof(tx_data_), &sent, 100) != 0) {
    // tools::logger()->warn("[Gimbal] Failed to write USB bulk.");
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

  int sent = 0;
  if (!handle_ || libusb_bulk_transfer(handle_, ep_out_, reinterpret_cast<uint8_t *>(&tx_data_), sizeof(tx_data_), &sent, 100) != 0) {
    // tools::logger()->warn("[Gimbal] Failed to write USB bulk.");
  }
}

void Gimbal::send_video(const uint8_t * video_data, size_t size)
{
  if (size != 300) {
    tools::logger()->warn("[Gimbal] Invalid video packet size: {}", size);
    return;
  }

  VideoToGimbal pkt;
  pkt.head[0] = 'S';
  pkt.head[1] = 'V';
  std::memcpy(pkt.data, video_data, size);
  pkt.crc16 = tools::get_crc16(
    reinterpret_cast<uint8_t *>(&pkt), sizeof(pkt) - sizeof(pkt.crc16));

  int sent = 0;
  if (!handle_ || libusb_bulk_transfer(handle_, ep_out_, reinterpret_cast<uint8_t *>(&pkt), sizeof(pkt), &sent, 100) != 0) {
    // tools::logger()->warn("[Gimbal] Failed to write video packet.");
  }
}

bool Gimbal::read(uint8_t * buffer, size_t size)
{
  if (!handle_) return false;
  int transferred = 0;
  int r = libusb_bulk_transfer(handle_, ep_in_, buffer, size, &transferred, 100);
  return (r == 0 && transferred == static_cast<int>(size));
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

    if (!read(reinterpret_cast<uint8_t *>(&rx_data_), sizeof(rx_data_.head))) {
      error_count++;
      continue;
    }

    if (rx_data_.head[0] != 'S' || rx_data_.head[1] != 'P') continue;

    auto t = std::chrono::steady_clock::now();

    if (!read(
          reinterpret_cast<uint8_t *>(&rx_data_) + sizeof(rx_data_.head),
          sizeof(rx_data_) - sizeof(rx_data_.head))) {
      error_count++;
      continue;
    }

    if (!tools::check_crc16(reinterpret_cast<uint8_t *>(&rx_data_), sizeof(rx_data_))) {
      tools::logger()->debug("[Gimbal] CRC16 check failed.");
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
  }

  tools::logger()->info("[Gimbal] read_thread stopped.");
}

void Gimbal::reconnect()
{
  int max_retry_count = 10;
  for (int i = 0; i < max_retry_count && !quit_; ++i) {
    tools::logger()->warn("[Gimbal] Reconnecting USB, attempt {}/{}...", i + 1, max_retry_count);
    
    if (handle_) {
      libusb_release_interface(handle_, interface_num_);
      libusb_close(handle_);
      handle_ = nullptr;
    }
    
    std::this_thread::sleep_for(std::chrono::seconds(1));

    handle_ = libusb_open_device_with_vid_pid(ctx_, vid_, pid_);
    if (handle_) {
      if (libusb_kernel_driver_active(handle_, interface_num_) == 1) {
        libusb_detach_kernel_driver(handle_, interface_num_);
      }
      if (libusb_claim_interface(handle_, interface_num_) >= 0) {
        queue_.clear();
        tools::logger()->info("[Gimbal] Reconnected USB successfully.");
        break;
      }
      libusb_close(handle_);
      handle_ = nullptr;
    }
    tools::logger()->warn("[Gimbal] Reconnect failed.");
  }
}

}  // namespace io