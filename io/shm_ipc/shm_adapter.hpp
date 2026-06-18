#pragma once

#include <Eigen/Geometry>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <memory>
#include "shm_client.hpp"

namespace io {

// ===== 云台状态结构（与 sim_imu.hpp 中的 SimIMUState 保持一致） =====
struct SimIMUState
{
  float yaw = 0.0f;          // 角度制
  float yaw_vel = 0.0f;
  float pitch = 0.0f;        // 角度制
  float pitch_vel = 0.0f;
  float bullet_speed = 0.0f;
  uint16_t bullet_count = 0;
  int8_t yaw_offset = 0;
  int8_t pitch_offset = 0;
};

/**
 * @brief 共享内存适配器 - 提供与 Camera/SimIMU 类似的接口
 * 
 * 替代 ROS2 的 subscribe2sim 和 publish2sim
 */
class ShmAdapter {
public:
    ShmAdapter();
    ~ShmAdapter() = default;

    // 检查连接状态
    bool is_connected() const { return connected_; }

    // ===== 图像读取 =====
    bool read_image(cv::Mat& img, std::chrono::steady_clock::time_point& timestamp);
    bool read_image_zero_copy(cv::Mat& img, uint64_t& seq, uint64_t& timestamp_ns);
    bool has_new_image() const;

    // ===== 云台姿态读取 =====
    bool read_gimbal_pose(Eigen::Quaterniond& quat, uint64_t& timestamp_ns) const;
    bool read_gimbal_euler(float& yaw_deg, float& pitch_deg, float& roll_deg) const;
    
    // ===== 获取云台状态（与 SimIMU 接口兼容） =====
    SimIMUState state() const;
    
    // ===== 云台指令发送 =====
    void send_gimbal_cmd(float yaw_deg, float pitch_deg, float distance_m, bool fire);

    // ===== 相机信息 =====
    ipc::CameraInfo camera_info() const;

    // ===== 调试 =====
    void print_status() const;

private:
    std::unique_ptr<ipc::ShmClient> client_;
    bool connected_;
    
    // 缓存上一帧姿态（用于降级）
    mutable Eigen::Quaterniond last_quat_;
    mutable bool has_last_quat_{false};
    
    // 缓存的状态
    mutable SimIMUState cached_state_;
    mutable bool has_cached_state_{false};
};

} // namespace io