#include "xrobot_imu.hpp"

#include "tools/crc.hpp"
#include "tools/logger.hpp"
#include "tools/math_tools.hpp"
#include "tools/yaml.hpp"

namespace io
{
XrobotImu::XrobotImu(const std::string & config_path)
{
  auto yaml = tools::load(config_path);
  auto com_port = tools::read<std::string>(yaml, "imu_com_port");
  auto baudrate = tools::read<int>(yaml, "imu_baudrate", 1000000);

  try {
    serial_.setPort(com_port);
    serial_.setBaudrate(baudrate);
    serial_.open();
    tools::logger()->info("[XrobotImu] Opened {} at {} baud.", com_port, baudrate);
  } catch (const std::exception & e) {
    tools::logger()->error("[XrobotImu] Failed to open serial: {}", e.what());
    exit(1);
  }

  thread_ = std::thread(&XrobotImu::read_thread, this);
}

XrobotImu::~XrobotImu()
{
  quit_ = true;
  if (thread_.joinable()) thread_.join();
  serial_.close();
  tools::logger()->info("[XrobotImu] Closed.");
}

ImuState XrobotImu::state() const
{
  std::lock_guard<std::mutex> lock(mutex_);
  return state_;
}

Eigen::Quaterniond XrobotImu::q(std::chrono::steady_clock::time_point t)
{
  while (true) {
    auto [q_a, t_a] = q_queue_.pop();
    auto [q_b, t_b] = q_queue_.front();
    auto t_ab = tools::delta_time(t_a, t_b);
    auto t_ac = tools::delta_time(t_a, t);
    auto k = t_ac / t_ab;
    Eigen::Quaterniond q_c = q_a.slerp(k, q_b).normalized();
    if (t < t_a) return q_c;
    if (!(t_a < t && t <= t_b)) continue;

    return q_c;
  }
}

Eigen::Vector3d XrobotImu::euler(std::chrono::steady_clock::time_point t)
{
  while (true) {
    auto [euler_a, t_a] = euler_queue_.pop();
    auto [euler_b, t_b] = euler_queue_.front();
    auto t_ab = tools::delta_time(t_a, t_b);
    auto t_ac = tools::delta_time(t_a, t);
    auto k = t_ac / t_ab;
    Eigen::Vector3d euler_c = euler_a + k * (euler_b - euler_a);
    if (t < t_a) return euler_c;
    if (!(t_a < t && t <= t_b)) continue;

    return euler_c;
  }
}

Eigen::Vector3d XrobotImu::gyro(std::chrono::steady_clock::time_point t)
{
  while (true) {
    auto [gyro_a, t_a] = gyro_queue_.pop();
    auto [gyro_b, t_b] = gyro_queue_.front();
    auto t_ab = tools::delta_time(t_a, t_b);
    auto t_ac = tools::delta_time(t_a, t);
    auto k = t_ac / t_ab;
    Eigen::Vector3d gyro_c = gyro_a + k * (gyro_b - gyro_a);
    if (t < t_a) return gyro_c;
    if (!(t_a < t && t <= t_b)) continue;

    return gyro_c;
  }
}

Eigen::Vector3d XrobotImu::accl(std::chrono::steady_clock::time_point t)
{
  while (true) {
    auto [accl_a, t_a] = accl_queue_.pop();
    auto [accl_b, t_b] = accl_queue_.front();
    auto t_ab = tools::delta_time(t_a, t_b);
    auto t_ac = tools::delta_time(t_a, t);
    auto k = t_ac / t_ab;
    Eigen::Vector3d accl_c = accl_a + k * (accl_b - accl_a);
    if (t < t_a) return accl_c;
    if (!(t_a < t && t <= t_b)) continue;

    return accl_c;
  }
}

bool XrobotImu::read(uint8_t * buffer, size_t size)
{
  try {
    return serial_.read(buffer, size) == size;
  } catch (const std::exception & e) {
    // tools::logger()->warn("[XrobotImu] Failed to read serial: {}", e.what());
    return false;
  }
}

void XrobotImu::read_thread()
{
  tools::logger()->info("[XrobotImu] read_thread started.");
  int error_count = 0;

  while (!quit_) {
    if (error_count > 5000) {
      error_count = 0;
      tools::logger()->warn("[XrobotImu] Too many errors, attempting to reconnect...");
      reconnect();
      continue;
    }

    // 读取前缀
    if (!read(&rx_data_.prefix, sizeof(rx_data_.prefix))) {
      error_count++;
      continue;
    }

    // 检查前缀
    if (rx_data_.prefix != 0xA5) {
      // 如果不是IMU数据，跳过
      error_count++;
      continue;
    }

    auto t = std::chrono::steady_clock::now();

    // 读取剩余数据
    if (!read(reinterpret_cast<uint8_t *>(&rx_data_) + sizeof(rx_data_.prefix),
              sizeof(rx_data_) - sizeof(rx_data_.prefix))) {
      error_count++;
      continue;
    }

    // CRC校验
    if (!tools::check_crc8(reinterpret_cast<uint8_t *>(&rx_data_), sizeof(rx_data_))) {
      tools::logger()->debug("[XrobotImu] CRC8 check failed.");
      continue;
    }

    error_count = 0;
    
    // 更新状态
    {
      std::lock_guard<std::mutex> lock(mutex_);
      
      // 四元数 (注意：IMU中的q0是实部，Eigen的Quaterniond构造参数为(w, x, y, z))
      Eigen::Quaterniond q(rx_data_.q[0], rx_data_.q[1], rx_data_.q[2], rx_data_.q[3]);
      state_.q = q;
      q_queue_.push({q, t});
      
      // 角速度
      Eigen::Vector3d gyro(rx_data_.gyro[0], rx_data_.gyro[1], rx_data_.gyro[2]);
      state_.gyro = gyro;
      gyro_queue_.push({gyro, t});
      
      // 加速度
      Eigen::Vector3d accl(rx_data_.accl[0], rx_data_.accl[1], rx_data_.accl[2]);
      state_.accl = accl;
      accl_queue_.push({accl, t});
      
      // 欧拉角 (roll, pitch, yaw)
      Eigen::Vector3d euler(rx_data_.euler[0], rx_data_.euler[1], rx_data_.euler[2]);
      state_.euler = euler;
      euler_queue_.push({euler, t});
      
      // 时间戳
      state_.time = rx_data_.time;
      state_.sync = rx_data_.sync;
    }
  }

  tools::logger()->info("[XrobotImu] read_thread stopped.");
}

void XrobotImu::reconnect()
{
  int max_retry_count = 10;
  for (int i = 0; i < max_retry_count && !quit_; ++i) {
    tools::logger()->warn("[XrobotImu] Reconnecting serial, attempt {}/{}...", i + 1, max_retry_count);
    try {
      serial_.close();
      std::this_thread::sleep_for(std::chrono::seconds(1));
    } catch (...) {
    }

    try {
      serial_.open();
      q_queue_.clear();
      euler_queue_.clear();
      gyro_queue_.clear();
      accl_queue_.clear();
      tools::logger()->info("[XrobotImu] Reconnected serial successfully.");
      break;
    } catch (const std::exception & e) {
      tools::logger()->warn("[XrobotImu] Reconnect failed: {}", e.what());
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
  }
}

}  // namespace io