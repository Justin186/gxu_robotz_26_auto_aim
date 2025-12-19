#ifndef IO__XROBOT_IMU_HPP
#define IO__XROBOT_IMU_HPP

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
struct __attribute__((packed)) ImuData
{
  uint8_t prefix = 0xA5;
  uint64_t time : 40;
  uint64_t sync : 40;
  float q[4];      // 四元数 q0, q1, q2, q3
  float gyro[3];   // 角速度 x, y, z
  float accl[3];   // 加速度 x, y, z
  float euler[3];  // 欧拉角 roll, pitch, yaw
  uint8_t crc8;
};

static_assert(sizeof(ImuData) <= 64);

struct ImuState
{
  Eigen::Quaterniond q;
  Eigen::Vector3d gyro;
  Eigen::Vector3d accl;
  Eigen::Vector3d euler;
  uint64_t time;
  uint64_t sync;
};

class XrobotImu
{
public:
  XrobotImu(const std::string & config_path);
  ~XrobotImu();

  ImuState state() const;
  Eigen::Quaterniond q(std::chrono::steady_clock::time_point t);
  Eigen::Vector3d euler(std::chrono::steady_clock::time_point t);
  Eigen::Vector3d gyro(std::chrono::steady_clock::time_point t);
  Eigen::Vector3d accl(std::chrono::steady_clock::time_point t);

private:
  serial::Serial serial_;
  
  std::thread thread_;
  std::atomic<bool> quit_ = false;
  mutable std::mutex mutex_;
  
  ImuData rx_data_;
  ImuState state_;
  
  // 队列存储四元数和时间戳，用于插值
  tools::ThreadSafeQueue<std::tuple<Eigen::Quaterniond, std::chrono::steady_clock::time_point>>
    q_queue_{1000};
  // 队列存储欧拉角和时间戳
  tools::ThreadSafeQueue<std::tuple<Eigen::Vector3d, std::chrono::steady_clock::time_point>>
    euler_queue_{1000};
  // 队列存储角速度和时间戳
  tools::ThreadSafeQueue<std::tuple<Eigen::Vector3d, std::chrono::steady_clock::time_point>>
    gyro_queue_{1000};
  // 队列存储加速度和时间戳
  tools::ThreadSafeQueue<std::tuple<Eigen::Vector3d, std::chrono::steady_clock::time_point>>
    accl_queue_{1000};
  
  bool read(uint8_t * buffer, size_t size);
  void read_thread();
  void reconnect();
  void update_state();
};

}  // namespace io

#endif  // IO__XROBOT_IMU_HPP