#include "shm_adapter.hpp"
#include <iostream>
#include <cmath>

namespace io {

ShmAdapter::ShmAdapter() 
    : connected_(false), has_last_quat_(false)
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
    
    // 共享内存中的图像是 RGB 格式，需要转换为 BGR（OpenCV 默认）
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

bool ShmAdapter::consume_next_frame(cv::Mat& img, std::chrono::steady_clock::time_point& timestamp)
{
    if (!connected_) return false;

    // 1. 优先取图像；若无新帧则不消费任何东西，交由上层自行调度。
    if (!read_image(img, timestamp)) {
        return false;
    }

    // 2. 消费本轮其余位姿通道，满足 sim 的捆绑式同步发布门控。
    //
    //    新版 sim(talos-ipc) 只有在 image 与 gimbal/odom/muzzle/camera 五路全部被消费
    //    后才能发布下一帧。任一通道残留 dirty 标志都会被 sim 视为"消费者未跟上"而从
    //    此拒发新帧，令客户端在 read_image() 上空转、貌似卡死。
    //
    //    · gimbal 经 read_gimbal_pose() 消费，其内部 last-quat 降级缓存保证了上层事后
    //      依旧能取到最近一次的云台姿态，二者互不干扰。
    //    · odom/muzzle/camera 仅为满足门控而消费，返回值在此有意忽略。
    {
        Eigen::Quaterniond tmp_q;
        Eigen::Vector3d tmp_pos;
        uint64_t dummy_ts;
        (void)read_gimbal_pose(tmp_q, dummy_ts);
        (void)read_odom_pose(tmp_q, tmp_pos, dummy_ts);
        (void)read_muzzle_pose(tmp_q, tmp_pos, dummy_ts);
        (void)read_camera_pose(tmp_q, tmp_pos, dummy_ts);
    }

    return true;
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
    // 每次调用均实时读取云台欧拉角，绝不缓存——
    // 原先的永久缓存会使 yaw/pitch 永远停留在首个采样值，导致下游控制失准。
    SimIMUState s;

    float yaw_deg, pitch_deg, roll_deg;
    if (read_gimbal_euler(yaw_deg, pitch_deg, roll_deg)) {
        s.yaw = yaw_deg;
        s.pitch = pitch_deg;
    }

    return s;
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

bool ShmAdapter::read_chassis_observation(ipc::ChassisObservation& chassis) const
{
    if (!connected_) return false;
    auto opt = client_->recv_chassis_observation();
    if (!opt) return false;
    chassis = *opt;
    return true;
}

bool ShmAdapter::read_ground_truth(ipc::GroundTruthBatch& gt) const
{
    if (!connected_) return false;
    auto opt = client_->recv_ground_truth();
    if (!opt) return false;
    gt = *opt;
    return true;
}

bool ShmAdapter::read_runtime_state(ipc::RuntimeState& state) const
{
    if (!connected_) return false;
    auto opt = client_->recv_runtime_state();
    if (!opt) return false;
    state = *opt;
    return true;
}

bool ShmAdapter::read_odom_pose(Eigen::Quaterniond& quat, Eigen::Vector3d& pos, uint64_t& timestamp_ns) const
{
    if (!connected_) return false;
    auto pose = client_->recv_pose(ipc::POSE_ODOM);
    if (!pose) return false;
    quat.w() = pose->qw; quat.x() = pose->qx; quat.y() = pose->qy; quat.z() = pose->qz;
    pos.x() = pose->x; pos.y() = pose->y; pos.z() = pose->z;
    timestamp_ns = pose->timestamp_ns;
    return true;
}

bool ShmAdapter::read_muzzle_pose(Eigen::Quaterniond& quat, Eigen::Vector3d& pos, uint64_t& timestamp_ns) const
{
    if (!connected_) return false;
    auto pose = client_->recv_pose(ipc::POSE_MUZZLE);
    if (!pose) return false;
    quat.w() = pose->qw; quat.x() = pose->qx; quat.y() = pose->qy; quat.z() = pose->qz;
    pos.x() = pose->x; pos.y() = pose->y; pos.z() = pose->z;
    timestamp_ns = pose->timestamp_ns;
    return true;
}

bool ShmAdapter::read_camera_pose(Eigen::Quaterniond& quat, Eigen::Vector3d& pos, uint64_t& timestamp_ns) const
{
    if (!connected_) return false;
    auto pose = client_->recv_pose(ipc::POSE_CAMERA);
    if (!pose) return false;
    quat.w() = pose->qw; quat.x() = pose->qx; quat.y() = pose->qy; quat.z() = pose->qz;
    pos.x() = pose->x; pos.y() = pose->y; pos.z() = pose->z;
    timestamp_ns = pose->timestamp_ns;
    return true;
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