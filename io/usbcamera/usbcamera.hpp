#ifndef IO__USBCamera_HPP
#define IO__USBCamera_HPP

#include <chrono>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <thread>

namespace io
{
class USBCamera
{
public:
  USBCamera(const std::string & open_name, const std::string & config_path);
  ~USBCamera();
  cv::Mat read();
  void read(cv::Mat & img, std::chrono::steady_clock::time_point & timestamp);
  bool try_read(cv::Mat & img, std::chrono::steady_clock::time_point & timestamp);
  void clear_buffer();
  std::string device_name;

private:
  std::mutex cap_mutex_;
  std::mutex latest_mutex_;
  cv::VideoCapture cap_;
  cv::Mat img_;
  cv::Mat latest_img_;
  std::chrono::steady_clock::time_point latest_timestamp_;
  bool has_latest_ = false;
  std::string open_name_;
  int usb_exposure_, usb_frame_rate_, sharpness_;
  int open_count_;
  double image_width_, image_height_;
  int usb_gamma_, usb_gain_;
  bool quit_, ok_;
  std::thread capture_thread_;
  std::thread daemon_thread_;

  void try_open();
  void open();
  void close();
};

}  // namespace io

#endif
