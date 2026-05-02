#include "perceptron.hpp"

#include <cmath>
#include <chrono>
#include <memory>
#include <thread>

#include "tasks/auto_aim/yolo.hpp"
#include "tools/exiter.hpp"
#include "tools/logger.hpp"
#include "tools/math_tools.hpp"

namespace omniperception
{

ScanResult omni_scan(double dt, ScanState & state)
{
  double delta_angle = 60.0;
  double amplitude = 25.0;
  double period = 0.75;

  state.scan_cmd_angle += delta_angle * dt;

  double yaw = tools::limit_rad(state.scan_cmd_angle / 57.3);
  double pitch =
    tools::limit_rad(amplitude * std::sin(2 * M_PI * state.scan_t / period) / 57.3 - 0.15);

  state.scan_t += dt;
  if (state.scan_t >= period) {
    state.scan_t -= period;
  }

  return {yaw, pitch};
}

ScanResult short_lost_scan(double start_yaw_deg, double dt, ScanState & state)
{
  double delta_angle = 150.0; // yaw速度v
  double amplitude = 30.0; // pitch振幅，单位degree
  double period = 0.75; // pitch周期

  state.scan_cmd_angle += state.scan_direction * delta_angle * dt;

  if (state.scan_cmd_angle <= start_yaw_deg - 15.0) {
    state.scan_cmd_angle = start_yaw_deg - 15.0;
    state.scan_direction = 1;
    state.direction_changes++;
  } else if (state.scan_cmd_angle >= start_yaw_deg + 15.0) {
    state.scan_cmd_angle = start_yaw_deg + 15.0;
    state.scan_direction = -1;
    state.direction_changes++;
  }

  if (state.direction_changes >= 4) {
    state.use_omni_scan = true;
  }

  double yaw = tools::limit_rad(state.scan_cmd_angle / 57.3);
  double pitch =
    tools::limit_rad(amplitude * std::sin(2 * M_PI * state.scan_t / period) / 57.3 - 0.1);

  state.scan_t += dt;
  if (state.scan_t >= period) {
    state.scan_t -= period;
  }

  return {yaw, pitch};
}

ScanResult scan(double current_yaw, double dt, bool first_scan, ScanState & state)
{
  if (first_scan) {
    state.start_angle = current_yaw * 57.3;
    state.scan_cmd_angle = state.start_angle;
    state.scan_t = 0.0;
    state.scan_direction = -1;
    state.direction_changes = 0;
    state.use_omni_scan = false;
  }

  if (state.use_omni_scan) {
    return omni_scan(dt, state);
  } else {
    return short_lost_scan(state.start_angle, dt, state);
  }
}

Perceptron::Perceptron(
  io::CameraBase * usbcam1, io::CameraBase * usbcam2, const std::string & config_path)
: detection_queue_(10), decider_(config_path), stop_flag_(false)
{
  // 初始化 YOLO 模型
  yolo_parallel1_ = std::make_shared<auto_aim::YOLO>(config_path, false);
  yolo_parallel2_ = std::make_shared<auto_aim::YOLO>(config_path, false);


  std::this_thread::sleep_for(std::chrono::seconds(2));
  // 创建两个线程进行并行推理，并把识别结果放入线程安全队列中
  threads_.emplace_back([&] { parallel_infer(usbcam1, yolo_parallel1_); });
  threads_.emplace_back([&] { parallel_infer(usbcam2, yolo_parallel2_); });


  tools::logger()->info("Perceptron initialized.");
}

Perceptron::~Perceptron()
{
  {
    std::unique_lock<std::mutex> lock(mutex_);
    stop_flag_ = true;  // 设置退出标志
  }
  condition_.notify_all();  // 唤醒所有等待的线程

  // 等待线程结束
  for (auto & t : threads_) {
    if (t.joinable()) {
      t.join();
    }
  }
  tools::logger()->info("Perceptron destructed.");
}

//读取线程安全队列中的所有检测结果并返回一个包含这些结果的向量。这个函数会不断地从队列中取出检测结果，直到队列为空为止。
std::vector<DetectionResult> Perceptron::get_detection_queue()
{
  std::vector<DetectionResult> result;//包含检测结果
  DetectionResult temp;

  // 注意：这里的 pop 不阻塞（假设队列为空时会报错或忽略）
  while (!detection_queue_.empty()) {
    detection_queue_.pop(temp);//把队列中的第一个元素取出放到temp中
    result.push_back(std::move(temp));//std::move不复制而是直接转移数据进result，temp就空了.push_back把temp放到result的末尾
  }

  return result;
}

// 将并行推理逻辑移动到类成员函数，执行了读取图像，使用 YOLO 进行检测，并将结果推入线程安全队列的功能
void Perceptron::parallel_infer(
  io::CameraBase * cam, std::shared_ptr<auto_aim::YOLO> & yolov8_parallel)
{
  if (!cam) {
    tools::logger()->error("Camera pointer is null!");
    return;
  }
  try {
    while (true) {
      cv::Mat usb_img;
      std::chrono::steady_clock::time_point ts;

      {
        std::unique_lock<std::mutex> lock(mutex_);
        if (stop_flag_) break;  // 检查是否需要退出
      }

      cam->read(usb_img, ts);//这以后img就有数据了，yolo_parallel就可以用来检测了
      if (usb_img.empty()) {
        //std::this_thread::sleep_for(std::chrono::milliseconds(10));
        continue;
      }

      auto armors = yolov8_parallel->detect(usb_img);
      if (!armors.empty()) {
        auto delta_angle = decider_.delta_angle(armors, cam->device_name);

        DetectionResult dr;
        dr.armors = std::move(armors);
        dr.timestamp = ts;
        dr.delta_yaw = delta_angle[0] / 57.3;
        dr.delta_pitch = delta_angle[1] / 57.3;
        detection_queue_.push(dr);  // 推入线程安全队列
      }
    }
  } catch (const std::exception & e) {
    tools::logger()->error("Exception in parallel_infer: {}", e.what());
  }
}

}  // namespace omniperception
