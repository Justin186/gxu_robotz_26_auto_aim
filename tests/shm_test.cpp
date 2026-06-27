#include <fmt/core.h>
#include <fmt/chrono.h>

#include <chrono>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <thread>
#include <iomanip>
#include "tools/img_tools.hpp"

#include "io/shm_ipc/shm_adapter.hpp"

using namespace std::chrono_literals;

int main(int argc, char * argv[])
{
    std::cout << "========================================" << std::endl;
    std::cout << "   Shared Memory Debug Tool" << std::endl;
    std::cout << "========================================" << std::endl;

    // ===== 连接共享内存 =====
    io::ShmAdapter shm;
    if (!shm.is_connected()) {
        std::cerr << "[Error] Failed to connect to shared memory!" << std::endl;
        return 1;
    }
    shm.print_status();

    std::cout << "\n========================================" << std::endl;
    std::cout << "   Press 'q' to quit, any key to refresh" << std::endl;
    std::cout << "========================================" << std::endl;

    int frame_count = 0;
    cv::Mat img_display;

    while (true) {
        frame_count++;
        
        // ========== 1. 读取图像 ==========
        cv::Mat img;
        std::chrono::steady_clock::time_point t;
        bool has_image = shm.read_image(img, t);
        
        // ========== 2. 读取云台姿态 ==========
        Eigen::Quaterniond gimbal_q;
        uint64_t gimbal_ts;
        bool has_gimbal = shm.read_gimbal_pose(gimbal_q, gimbal_ts);
        
        float yaw_deg = 0, pitch_deg = 0, roll_deg = 0;
        if (has_gimbal) {
            shm.read_gimbal_euler(yaw_deg, pitch_deg, roll_deg);
        }

        // ========== 3. 读取相机内参 ==========
        ipc::CameraInfo cam_info = shm.camera_info();

        // ========== 4. 读取底盘观测 ==========
        ipc::ChassisObservation chassis;
        bool has_chassis = shm.read_chassis_observation(chassis);

        // ========== 5. 读取里程计位姿 ==========
        Eigen::Quaterniond odom_q;
        Eigen::Vector3d odom_pos;
        uint64_t odom_ts;
        bool has_odom = shm.read_odom_pose(odom_q, odom_pos, odom_ts);

        // ========== 6. 读取枪口位姿 ==========
        Eigen::Quaterniond muzzle_q;
        Eigen::Vector3d muzzle_pos;
        uint64_t muzzle_ts;
        bool has_muzzle = shm.read_muzzle_pose(muzzle_q, muzzle_pos, muzzle_ts);

        // ========== 7. 读取相机位姿 ==========
        Eigen::Quaterniond camera_q;
        Eigen::Vector3d camera_pos;
        uint64_t camera_ts;
        bool has_camera = shm.read_camera_pose(camera_q, camera_pos, camera_ts);

        // ========== 8. 读取 Ground Truth ==========
        ipc::GroundTruthBatch gt;
        bool has_gt = shm.read_ground_truth(gt);

        // ========== 9. 读取运行时状态 ==========
        ipc::RuntimeState runtime_state;
        bool has_runtime = shm.read_runtime_state(runtime_state);

        // ========== 打印到终端 ==========
        std::cout << "\n========================================" << std::endl;
        std::cout << "Frame: " << frame_count << std::endl;
        std::cout << "========================================" << std::endl;

        // 图像信息
        if (has_image) {
            std::cout << "[Image] " << img.cols << "x" << img.rows 
                      << ", Channels: " << img.channels() << std::endl;
        } else {
            std::cout << "[Image] No data" << std::endl;
        }

        // 云台姿态
        if (has_gimbal) {
            std::cout << fmt::format("[Gimbal] Yaw: {:.2f}°, Pitch: {:.2f}°, Roll: {:.2f}°", 
                       yaw_deg, pitch_deg, roll_deg) << std::endl;
            std::cout << fmt::format("         Quat: w={:.4f}, x={:.4f}, y={:.4f}, z={:.4f}",
                       gimbal_q.w(), gimbal_q.x(), gimbal_q.y(), gimbal_q.z()) << std::endl;
        } else {
            std::cout << "[Gimbal] No data" << std::endl;
        }

        // 相机内参
        if (cam_info.timestamp_ns > 0) {
            std::cout << fmt::format("[CameraInfo] fx={:.2f}, fy={:.2f}, cx={:.2f}, cy={:.2f}",
                       cam_info.fx, cam_info.fy, cam_info.cx, cam_info.cy) << std::endl;
            std::cout << fmt::format("              Width={}, Height={}",
                       cam_info.width, cam_info.height) << std::endl;
        }

        // 底盘观测
        if (has_chassis) {
            std::cout << fmt::format("[Chassis] vx={:.3f}, vy={:.3f}, wz={:.3f} rad/s",
                       chassis.v_body[0], chassis.v_body[1], chassis.wz_radps) << std::endl;
            std::cout << fmt::format("          rpy: roll={:.2f}°, pitch={:.2f}°, yaw={:.2f}°",
                       chassis.rpy_rad[0] * 57.3, chassis.rpy_rad[1] * 57.3, chassis.rpy_rad[2] * 57.3) << std::endl;
        }

        // 里程计位姿
        if (has_odom) {
            std::cout << fmt::format("[Odom] pos: ({:.3f}, {:.3f}, {:.3f})",
                       odom_pos.x(), odom_pos.y(), odom_pos.z()) << std::endl;
        }

        // 枪口位姿
        if (has_muzzle) {
            std::cout << fmt::format("[Muzzle] pos: ({:.3f}, {:.3f}, {:.3f})",
                       muzzle_pos.x(), muzzle_pos.y(), muzzle_pos.z()) << std::endl;
        }

        // 相机位姿
        if (has_camera) {
            std::cout << fmt::format("[Camera] pos: ({:.3f}, {:.3f}, {:.3f})",
                       camera_pos.x(), camera_pos.y(), camera_pos.z()) << std::endl;
        }

        // Ground Truth
        if (has_gt && gt.target_count > 0) {
            std::cout << fmt::format("[GroundTruth] {} targets, {} runes",
                       gt.target_count, gt.rune_count) << std::endl;
            for (uint32_t i = 0; i < std::min(gt.target_count, (uint32_t)5); i++) {
                auto& target = gt.targets[i];
                std::cout << fmt::format("  Target {}: pos=({:.3f}, {:.3f}, {:.3f}), yaw={:.2f}°",
                           i, target.position[0], target.position[1], target.position[2],
                           target.yaw * 57.3) << std::endl;
            }
            if (gt.target_count > 5) {
                std::cout << "  ... and " << (gt.target_count - 5) << " more" << std::endl;
            }
        }

        // 运行时状态
        if (has_runtime) {
            std::cout << fmt::format("[Runtime] following: {}", 
                       runtime_state.following ? "YES" : "NO") << std::endl;
        }

        // ========== 图像显示 ==========
        if (has_image) {
            img_display = img.clone();
            
            // 在图像上绘制信息
            int line_y = 30;
            tools::draw_text(img_display, fmt::format("Frame: {}", frame_count), {10, line_y}, {0, 255, 255});
            
            line_y += 35;
            if (has_gimbal) {
                tools::draw_text(img_display, fmt::format("Yaw: {:.2f}, Pitch: {:.2f}, Roll: {:.2f}", 
                           yaw_deg, pitch_deg, roll_deg), {10, line_y}, {0, 255, 0});
            }
            
            line_y += 35;
            if (has_odom) {
                tools::draw_text(img_display, fmt::format("Odom: ({:.2f}, {:.2f}, {:.2f})", 
                           odom_pos.x(), odom_pos.y(), odom_pos.z()), {10, line_y}, {255, 255, 0});
            }
            
            line_y += 35;
            if (has_chassis) {
                tools::draw_text(img_display, fmt::format("Chassis: vx={:.2f}, vy={:.2f}, wz={:.3f}", 
                           chassis.v_body[0], chassis.v_body[1], chassis.wz_radps), {10, line_y}, {0, 255, 255});
            }
            
            line_y += 35;
            if (has_gt && gt.target_count > 0) {
                tools::draw_text(img_display, fmt::format("GT Targets: {}", gt.target_count), {10, line_y}, {255, 255, 0});
                
                // 在图像上绘制 Ground Truth 目标位置
                for (uint32_t i = 0; i < std::min(gt.target_count, (uint32_t)10); i++) {
                    auto& target = gt.targets[i];
                    // 简单投影显示（实际需要用相机投影）
                    int x = 100 + i * 50;
                    int y = 200 + (int)(target.position[0] * 10);
                    cv::circle(img_display, cv::Point(x, y), 5, cv::Scalar(0, 255, 255), -1);
                    cv::putText(img_display, fmt::format("T{}", i), cv::Point(x-10, y-10), 
                                cv::FONT_HERSHEY_SIMPLEX, 0.4, cv::Scalar(0, 255, 255));
                }
            }
            
            cv::resize(img_display, img_display, {}, 0.6, 0.6);
            cv::imshow("SHM Debug", img_display);
        }

        // ========== 键盘输入 ==========
        auto key = cv::waitKey(1);
        if (key == 'q' || key == 'Q') {
            break;
        }

        // 等待刷新
        std::this_thread::sleep_for(16ms);  // ~60 FPS
    }

    std::cout << "\n[Debug] Shutting down..." << std::endl;
    return 0;
}