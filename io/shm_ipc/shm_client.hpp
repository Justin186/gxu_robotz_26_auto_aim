#pragma once

#include <chrono>
#include <optional>
#include <thread>
#include <opencv2/core.hpp>

#include "shm_layout.hpp"
#include "shm_region.hpp"
#include "shm_triple_buffer.hpp"

namespace ipc {

/**
 * @brief 共享内存 IPC 客户端
 */
class ShmClient {
public:
    struct ImageFrame {
        cv::Mat image;
        uint64_t seq;
        uint64_t timestamp_ns;
    };

    struct Pose {
        double x, y, z;
        double qw, qx, qy, qz;
        uint64_t frame_seq;
        uint64_t timestamp_ns;
    };

    ~ShmClient() = default;

    // Move-only
    ShmClient(ShmClient&&) = default;
    ShmClient& operator=(ShmClient&&) = default;
    ShmClient(const ShmClient&) = delete;
    ShmClient& operator=(const ShmClient&) = delete;

    /**
     * @brief 连接到共享内存 (消费者模式)
     */
    static std::optional<ShmClient> connect() {
        auto meta_result = ShmRegion::open(SHM_NAME_META, sizeof(ShmMetaRegion));
        if (!meta_result) {
            return std::nullopt;
        }

        auto pool_result = ShmRegion::open(SHM_NAME_IMAGE_POOL, IMAGE_POOL_SIZE);
        if (!pool_result) {
            return std::nullopt;
        }

        const auto* meta = meta_result->as<ShmMetaRegion>();
        if (meta->header.magic != SHM_MAGIC) {
            return std::nullopt;
        }
        if (meta->header.version != SHM_VERSION) {
            return std::nullopt;
        }

        return ShmClient(std::move(*meta_result), std::move(*pool_result));
    }

    /**
     * @brief 尝试接收最新图像帧
     */
    std::optional<ImageFrame> recv_image() const {
        ImageOps ops(&meta_->image);
        const auto slot = ops.borrow();
        if (!slot) {
            return std::nullopt;
        }

        const auto& img_meta = **slot;

        uint8_t* img_data = image_pool_ + img_meta.buffer_id * IMAGE_SIZE;

        int cv_type = CV_8UC3;
        if (img_meta.format == 1) cv_type = CV_8UC3;
        else if (img_meta.format == 2) cv_type = CV_8UC1;

        const cv::Mat image(
            static_cast<int>(img_meta.height), 
            static_cast<int>(img_meta.width), 
            cv_type, 
            img_data);

        return ImageFrame{
            .image = image,
            .seq = img_meta.seq,
            .timestamp_ns = img_meta.timestamp_ns,
        };
    }

    bool has_new_image() const {
        const ImageOps ops(&meta_->image);
        return ops.has_new_data();
    }

    /**
     * @brief 尝试接收指定类型的位姿
     */
    std::optional<Pose> recv_pose(const PoseIndex index) const {
        if (index > 4) return std::nullopt;

        PoseOps ops(&meta_->poses[index]);
        const auto slot = ops.borrow();
        if (!slot) {
            return std::nullopt;
        }

        const auto& pose = **slot;
        return Pose{
            .x = pose.position[0],
            .y = pose.position[1],
            .z = pose.position[2],
            .qw = pose.quaternion[0],
            .qx = pose.quaternion[1],
            .qy = pose.quaternion[2],
            .qz = pose.quaternion[3],
            .frame_seq = pose.frame_seq,
            .timestamp_ns = pose.timestamp_ns,
        };
    }

    /**
     * @brief 接收底盘观测数据
     */
    std::optional<ChassisObservation> recv_chassis_observation() const {
        const auto observation = meta_->chassis_observation;
        if (observation.timestamp_ns == 0) {
            return std::nullopt;
        }
        return observation;
    }

    /**
     * @brief 接收 ground truth 数据
     */
    std::optional<GroundTruthBatch> recv_ground_truth() const {
        const auto& gt = meta_->ground_truth;
        if (gt.timestamp_ns == 0) {
            return std::nullopt;
        }
        return gt;
    }

    /**
     * @brief 接收运行时状态
     */
    std::optional<RuntimeState> recv_runtime_state() const {
        const auto state = meta_->runtime_state;
        if (state.timestamp_ns == 0) {
            return std::nullopt;
        }
        return state;
    }

    /**
     * @brief 发布云台控制命令
     */
    void send_gimbal_cmd(
        const float yaw_deg, 
        const float pitch_deg, 
        const float distance_m,
        const bool fire_advice) const {
        GimbalOps ops(&meta_->gimbal_cmd);
        auto& cmd = ops.borrow_mut();

        cmd.timestamp_ns = now_ns();
        cmd.yaw_deg = yaw_deg;
        cmd.pitch_deg = pitch_deg;
        cmd.distance_m = distance_m;
        cmd.fire_advice = fire_advice ? 1 : 0;

        ops.publish();
    }

    const CameraInfo& camera_info() const { return meta_->camera_info; }

    const ShmHeader& header() const { return meta_->header; }

    void update_heartbeat() const { 
        meta_->header.heartbeat_ns = now_ns(); 
    }

    bool is_producer_alive(const uint64_t timeout_ns = 1'000'000'000) const {
        return now_ns() - meta_->header.heartbeat_ns < timeout_ns;
    }

    bool wait_for_producer(const std::chrono::milliseconds timeout = std::chrono::seconds(5)) const {
        const auto deadline = std::chrono::steady_clock::now() + timeout;
        while (std::chrono::steady_clock::now() < deadline) {
            if (is_producer_alive()) {
                return true;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
        return false;
    }

private:
    ShmClient(ShmRegion meta_region, ShmRegion pool_region)
        : meta_region_(std::move(meta_region))
        , pool_region_(std::move(pool_region))
        , meta_(meta_region_.as<ShmMetaRegion>())
        , image_pool_(static_cast<uint8_t*>(pool_region_.data())) {}

    static uint64_t now_ns() {
        return static_cast<uint64_t>(
            std::chrono::duration_cast<std::chrono::nanoseconds>(
                std::chrono::system_clock::now().time_since_epoch()
            ).count()
        );
    }

    ShmRegion meta_region_;
    ShmRegion pool_region_;
    ShmMetaRegion* meta_;
    uint8_t* image_pool_;
};

} // namespace ipc