#include "shm_adapter.hpp"
#include <iostream>
#include <cmath>

namespace io {

ShmAdapter::ShmAdapter() 
    : connected_(false), has_last_quat_(false), has_cached_state_(false)
{
    try {
        auto client_result = ipc::ShmClient::connect();
        if (!client_result) {
            std::cerr << "[ShmAdapter] Failed to connect to shared memory" << std::endl;
            return;
        }
        
        client_ = std::make_unique<ipc::ShmClient>(std::move(*client_result));
        
        // 等待生产者就绪（最多2秒）
        if (!client_->wait_for_producer(std::chrono::seconds(2))) {
            std::cerr << "[ShmAdapter] Producer not ready after 2s" << std::endl;
            return;
        }
        
        connected_ = true;
        std::cout << "[ShmAdapter] Connected to shared memory" << std::endl;
        std::cout << "  Image: " << client_->header().image_width 
                  << "x" << client_->header().image_height << std::endl;
        std::cout << "  Heartbeat: " << client_->header().heartbeat_ns << " ns" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "[ShmAdapter] Exception: " << e.what() << std::endl;
    }
}

bool ShmAdapter::read_image(cv::Mat& img, std::chrono::steady_clock::time_point& timestamp)
{
    if (!connected_) return false;
    
    auto frame = client_->recv_image();
    if (!frame) {
        return false;
    }
    
    // ===== 关键修复：RGB → BGR 转换 =====
    // 共享内存中的图像是 RGB 格式，OpenCV 默认 BGR
    cv::cvtColor(frame->image, img, cv::COLOR_RGB2BGR);
    timestamp = std::chrono::steady_clock::now();
    return true;
}

bool ShmAdapter::read_image_zero_copy(cv::Mat& img, uint64_t& seq, uint64_t& timestamp_ns)
{
    if (!connected_) return false;
    
    auto frame = client_->recv_image();
    if (!frame) {
        return false;
    }
    
    // 零拷贝，直接指向共享内存（注意：这是 RGB 格式）
    img = frame->image;
    seq = frame->seq;
    timestamp_ns = frame->timestamp_ns;
    return true;
}

bool ShmAdapter::has_new_image() const
{
    if (!connected_) return false;
    return client_->has_new_image();
}

bool ShmAdapter::read_gimbal_pose(Eigen::Quaterniond& quat, uint64_t& timestamp_ns) const
{
    if (!connected_) return false;
    
    auto pose = client_->recv_pose(ipc::POSE_GIMBAL);
    if (!pose) {
        if (has_last_quat_) {
            quat = last_quat_;
            return true;
        }
        return false;
    }
    
    quat.w() = pose->qw;
    quat.x() = pose->qx;
    quat.y() = pose->qy;
    quat.z() = pose->qz;
    quat.normalize();
    
    last_quat_ = quat;
    has_last_quat_ = true;
    timestamp_ns = pose->timestamp_ns;
    return true;
}

bool ShmAdapter::read_gimbal_euler(float& yaw_deg, float& pitch_deg, float& roll_deg) const
{
    Eigen::Quaterniond quat;
    uint64_t timestamp_ns;
    
    if (!read_gimbal_pose(quat, timestamp_ns)) {
        return false;
    }
    
    Eigen::Vector3d euler = quat.toRotationMatrix().eulerAngles(2, 1, 0);
    yaw_deg = euler.x() * 180.0 / M_PI;
    pitch_deg = euler.y() * 180.0 / M_PI;
    roll_deg = euler.z() * 180.0 / M_PI;
    return true;
}

SimIMUState ShmAdapter::state() const
{
    if (has_cached_state_) {
        return cached_state_;
    }
    
    float yaw_deg, pitch_deg, roll_deg;
    if (read_gimbal_euler(yaw_deg, pitch_deg, roll_deg)) {
        cached_state_.yaw = yaw_deg;
        cached_state_.pitch = pitch_deg;
        has_cached_state_ = true;
    }
    
    return cached_state_;
}

void ShmAdapter::send_gimbal_cmd(float yaw_deg, float pitch_deg, float distance_m, bool fire)
{
    if (!connected_) return;
    client_->send_gimbal_cmd(yaw_deg, pitch_deg, distance_m, fire);
}

ipc::CameraInfo ShmAdapter::camera_info() const
{
    if (!connected_) return ipc::CameraInfo{};
    return client_->camera_info();
}

void ShmAdapter::print_status() const
{
    if (!connected_) {
        std::cout << "[ShmAdapter] Status: DISCONNECTED" << std::endl;
        return;
    }
    
    std::cout << "[ShmAdapter] Status: CONNECTED" << std::endl;
    std::cout << "  Image: " << client_->header().image_width 
              << "x" << client_->header().image_height << std::endl;
    std::cout << "  Has new image: " << (has_new_image() ? "YES" : "NO") << std::endl;
}

} // namespace io