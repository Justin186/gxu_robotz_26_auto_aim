#include "usbcamera.hpp"

#include <stdexcept>

#include "tools/logger.hpp"
#include "tools/yaml.hpp"

using namespace std::chrono_literals;

namespace io
{
  //需要usb名字，比如video0。然后还需要初始化quit，作为守护线程的退出信号。
  //然后是ok_，表示摄像头是否成功打开。然后queue是一个线程安全的队列，大小为一。最后是open_count_，记录尝试打开摄像头的次数。
  //quit设为false放在开头的原因是，类初始化的时候会尝试打开摄像头，打开失败会保持false，重试
  //单开线程，并非共用
USBCamera::USBCamera(const std::string & open_name, const std::string & config_path)
: open_name_(open_name), quit_(false), ok_(false), queue_(1), open_count_(0)
{
  auto yaml = tools::load(config_path);
  image_width_ = tools::read<double>(yaml, "image_width");
  image_height_ = tools::read<double>(yaml, "image_height");
  usb_exposure_ = tools::read<double>(yaml, "usb_exposure");
  usb_frame_rate_ = tools::read<double>(yaml, "usb_frame_rate");
  usb_gamma_ = tools::read<double>(yaml, "usb_gamma");
  usb_gain_ = tools::read<double>(yaml, "usb_gain");
  try_open();

  // 守护线程
  daemon_thread_ = std::thread{[this] {
    // tools::logger()->info("daemon thread start");
    while (!quit_) {
      std::this_thread::sleep_for(100ms);//等待摄像头打开

      if (ok_) continue;

      if (open_count_ > 20) {
        tools::logger()->warn("Give up to open {} USB camera", this->device_name);
        quit_ = true;

        {
          std::lock_guard<std::mutex> lock(cap_mutex_);
          close();  // 先关闭摄像头
        }

        if (capture_thread_.joinable()) {
          tools::logger()->warn("Stopping capture thread");
          capture_thread_.join();
        }

        break;
      }

      if (capture_thread_.joinable()) capture_thread_.join();//joinable检查线程是否活跃，是就.join一直等待

      {
        std::lock_guard<std::mutex> lock(cap_mutex_);
        close();
      }
      try_open();
    }
    // tools::logger()->info("daemon thread exit");
  }};
}

USBCamera::~USBCamera()
{
  quit_ = true;
  {
    //通过互斥锁保护对摄像头的访问，确保在关闭摄像头时没有其他线程正在使用它。
    std::lock_guard<std::mutex> lock(cap_mutex_);
    close();
  }
  if (daemon_thread_.joinable()) daemon_thread_.join();
  if (capture_thread_.joinable()) capture_thread_.join();
  tools::logger()->info("USBCamera destructed.");
}

cv::Mat USBCamera::read()
{
  std::lock_guard<std::mutex> lock(cap_mutex_);
  if (!cap_.isOpened()) {
    tools::logger()->warn("Failed to read {} USB camera", this->device_name);
    return cv::Mat();
  }
  cap_ >> img_;
  return img_;
}

void USBCamera::read(cv::Mat & img, std::chrono::steady_clock::time_point & timestamp)
{
  CameraData data;
  queue_.pop(data);//把

  img = data.img;
  timestamp = data.timestamp;
}

void USBCamera::open()
{
  std::lock_guard<std::mutex> lock(cap_mutex_);
  std::string true_device_name = "/dev/" + open_name_;
  tools::logger()->info("Trying to open {} USB camera at {}", device_name, true_device_name);
  cap_.open(true_device_name, cv::CAP_V4L);
  if (!cap_.isOpened()) {
    tools::logger()->warn("Failed to open USB camera");
    return;
  }
  sharpness_ = cap_.get(cv::CAP_PROP_SHARPNESS);//读取锐度
  //通过写死锐度，然后在ubuntu系统上会先读取锐度，依此区分摄像头
  cap_.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));//用该格式MJPG，可以提高usb摄像头的帧率
  cap_.set(cv::CAP_PROP_FPS, usb_frame_rate_);//帧率设置
  cap_.set(cv::CAP_PROP_AUTO_EXPOSURE, 1);//关闭自动曝光，0是自动曝光，1是手动曝光
  cap_.set(cv::CAP_PROP_GAMMA, usb_gamma_);//伽马设置
  cap_.set(cv::CAP_PROP_GAIN, usb_gain_);//增益设置

  // if (sharpness_ == 2) {
  //   device_name = "left";
  //   cap_.set(cv::CAP_PROP_FRAME_WIDTH, image_width_);
  //   cap_.set(cv::CAP_PROP_FRAME_HEIGHT, image_height_);
  //   cap_.set(cv::CAP_PROP_EXPOSURE, usb_exposure_);
  // } else if (sharpness_ == 3) {
  //   device_name = "right";
  //   cap_.set(cv::CAP_PROP_FRAME_WIDTH, image_width_);
  //   cap_.set(cv::CAP_PROP_FRAME_HEIGHT, image_height_);
  //   cap_.set(cv::CAP_PROP_EXPOSURE, usb_exposure_);
  // }

  tools::logger()->info("{} USBCamera opened", device_name);
  // tools::logger()->info("USBCamera exposure time:{}", cap_.get(cv::CAP_PROP_EXPOSURE));
  tools::logger()->info("USBCamera fps:{}", cap_.get(cv::CAP_PROP_FPS));
  // tools::logger()->info("USBCamera gamma:{}", cap_.get(cv::CAP_PROP_GAMMA));

  // 取图线程
  capture_thread_ = std::thread{[this] {
    ok_ = true;
    std::this_thread::sleep_for(50ms);
    tools::logger()->info("[{} USB camera] capture thread started ", this->device_name);
    while (!quit_) {
      std::this_thread::sleep_for(1ms);

      cv::Mat img;
      bool success;
      {
        std::lock_guard<std::mutex> lock(cap_mutex_);
        if (!cap_.isOpened()) {
          break;
        }
        success = cap_.read(img);
      }

      if (!success) {
        tools::logger()->warn("Failed to read frame, exiting capture thread");
        break;
      }

      auto timestamp = std::chrono::steady_clock::now();
      queue_.push({img, timestamp});
    }
    ok_ = false;
  }};
}

void USBCamera::try_open()
{
  try {
    open();
    open_count_++;
  } catch (const std::exception & e) {
    tools::logger()->warn("{}", e.what());
  }
}

void USBCamera::close()
{
  if (cap_.isOpened()) {
    cap_.release();
    tools::logger()->info("USB camera released.");
  }
}

}  // namespace io