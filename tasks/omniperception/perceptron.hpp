#ifndef OMNIPERCEPTION__PERCEPTRON_HPP
#define OMNIPERCEPTION__PERCEPTRON_HPP

#include <chrono>
#include <condition_variable>
#include <list>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

#include "decider.hpp"
#include "detection.hpp"
#include "io/camera_base.hpp"
#include "tasks/auto_aim/armor.hpp"
#include "tasks/auto_aim/yolo.hpp"
#include "tools/thread_pool.hpp"
#include "tools/thread_safe_queue.hpp"

namespace omniperception
{

struct ScanResult
{
  double yaw;
  double pitch;
};

struct ScanState
{
  double start_angle = 0.0;
  double scan_cmd_angle = 0.0;
  double scan_t = 0.0;
  bool use_omni_scan = false;
};

ScanResult omni_scan(double dt, ScanState & state);
ScanResult short_lost_scan(double start_yaw_deg, double dt, ScanState & state);
ScanResult scan(double current_yaw, double dt, bool first_scan, ScanState & state);

class Perceptron
{
public:
  Perceptron(
    io::CameraBase * usbcma1, io::CameraBase * usbcam2, const std::string & config_path);

  ~Perceptron();

  std::vector<DetectionResult> get_detection_queue();

  void parallel_infer(io::CameraBase * cam, std::shared_ptr<auto_aim::YOLO> & yolo_parallel);

private:
  std::vector<std::thread> threads_;
  tools::ThreadSafeQueue<DetectionResult> detection_queue_;

  std::shared_ptr<auto_aim::YOLO> yolo_parallel1_;
  std::shared_ptr<auto_aim::YOLO> yolo_parallel2_;


  Decider decider_;
  bool stop_flag_;
  mutable std::mutex mutex_;
  std::condition_variable condition_;
};

}  // namespace omniperception
#endif
