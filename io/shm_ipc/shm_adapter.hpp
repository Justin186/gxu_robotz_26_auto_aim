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

    /**
     * @brief 消费一整轮话题集，满足 sim 的捆绑式同步发布门控。
     *
     * 新版 sim(talos-ipc) 只有在消费者把上一轮的 image 与 gimbal/odom/muzzle/camera
     * 五个主题全部消费完之后，才会发布下一帧。若任一位姿遗留 dirty 标志，sim 便不再
     * 产出新帧，客户端会因此在 read_image() 上空转而表现出"窗口不显示/疑似卡死"。
     *
     * 本方法在读取图像的同时，将该轮其余的位姿通道一并消费(drain)。其中 gimbal 借助
     * ShmAdapter 自身的 last-quat 降级缓存完成消费，故上层此后仍可通过 read_gimbal_pose()
     * 取得最近一次的云台姿态，互不冲突。
     *
     * @note 适用于需要持续跟进 sim 画面的入口(auto_aim_sim_shm 等)；单纯离线解析录像
     *       或其他不依赖 sim 同步门的场景仍可使用原始的 read_image()。
     *
     * @param img       输出：收到的图像(BGR)。
     * @param timestamp 输出：接收时刻。
     * @return true 表示本轮确有新图像并被消费；false 表示暂无可消费的新帧。
     */
    bool consume_next_frame(cv::Mat& img, std::chrono::steady_clock::time_point& timestamp);

    // ===== 云台姿态读取 =====
    bool read_gimbal_pose(Eigen::Quaterniond& quat, uint64_t& timestamp_ns) const;
    bool read_gimbal_euler(float& yaw_deg, float& pitch_deg, float& roll_deg) const;

    // ===== 获取云台状态（与 SimIMU 接口兼容） =====
    SimIMUState state() const;
    
    // ===== 云台指令发送 =====
    void send_gimbal_cmd(float yaw_deg, float pitch_deg, float distance_m, bool fire);

    // ===== 相机信息 =====
    ipc::CameraInfo camera_info() const;

    // ===== 底盘观测 =====
    bool read_chassis_observation(ipc::ChassisObservation& chassis) const;
    
    // ===== Ground Truth =====
    bool read_ground_truth(ipc::GroundTruthBatch& gt) const;
    
    // ===== 运行时状态 =====
    bool read_runtime_state(ipc::RuntimeState& state) const;
    
    // ===== 里程计位姿 =====
    bool read_odom_pose(Eigen::Quaterniond& quat, Eigen::Vector3d& pos, uint64_t& timestamp_ns) const;
    
    // ===== 枪口位姿 =====
    bool read_muzzle_pose(Eigen::Quaterniond& quat, Eigen::Vector3d& pos, uint64_t& timestamp_ns) const;
    
    // ===== 相机位姿 =====
    bool read_camera_pose(Eigen::Quaterniond& quat, Eigen::Vector3d& pos, uint64_t& timestamp_ns) const;

    // ===== 调试 =====
    void print_status() const;

private:
    std::unique_ptr<ipc::ShmClient> client_;
    bool connected_;
    
    // 缓存上一帧姿态（用于降级）
    mutable Eigen::Quaterniond last_quat_;
    mutable bool has_last_quat_{false};
};

} // namespace io