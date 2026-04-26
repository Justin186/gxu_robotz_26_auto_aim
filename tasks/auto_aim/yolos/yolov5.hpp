#ifndef AUTO_AIM__YOLOV5_HPP
#define AUTO_AIM__YOLOV5_HPP

#include <list>
#include <opencv2/opencv.hpp>
#include <memory>
#include <array>
#include <cstdint>
class TRTInfer;
#include <string>
#include <vector>

#include "tasks/auto_aim/armor.hpp"
#include "tasks/auto_aim/detector.hpp"
#include "tasks/auto_aim/yolo.hpp"

namespace auto_aim
{
class YOLOV5 : public YOLOBase
{
public:
  YOLOV5(const std::string & config_path, bool debug);

  std::list<Armor> detect(const cv::Mat & bgr_img, int frame_count) override;

  std::list<Armor> detect(const cv::Mat & bgr_img, int frame_count, cv::Mat & out_debug_img) override;

  std::list<Armor> postprocess(
    double scale, cv::Mat & output, const cv::Mat & bgr_img, int frame_count) override;

private:
  std::string device_, model_path_;
  std::string save_path_, debug_path_;
  bool debug_, use_roi_, use_traditional_;
  bool use_trt_{false};

  const int class_num_ = 13;
  const float nms_threshold_ = 0.3;
  const float score_threshold_ = 0.7;
  double min_confidence_, binary_threshold_;

  std::unique_ptr<TRTInfer> trt_infer_;
  cv::dnn::Net yolo_net_;
  cv::Mat net_input_;
  cv::Mat blob_;
  std::vector<uint16_t> trt_input_buffer_;
  std::vector<float> trt_output_buffer_;
  std::vector<int> parse_color_ids_;
  std::vector<int> parse_num_ids_;
  std::vector<float> parse_confidences_;
  std::vector<cv::Rect> parse_boxes_;
  std::vector<std::array<cv::Point2f, 4>> parse_keypoints_;

  cv::Rect roi_;
  cv::Point2f offset_;
  cv::Mat tmp_img_;

  Detector detector_;
  friend class MultiThreadDetector;

  bool check_name(const Armor & armor) const;
  bool check_type(const Armor & armor) const;

  cv::Point2f get_center_norm(const cv::Mat & bgr_img, const cv::Point2f & center) const;

  std::list<Armor> parse(double scale, cv::Mat & output, const cv::Mat & bgr_img, int frame_count, cv::Mat * out_debug_img = nullptr);

  std::list<Armor> detect_impl(const cv::Mat & raw_img, int frame_count, cv::Mat * out_debug_img);

  void save(const Armor & armor) const;
  void draw_detections(const cv::Mat & img, const std::list<Armor> & armors, int frame_count, cv::Mat * out_debug_img = nullptr) const;
  double sigmoid(double x);
};

}  // namespace auto_aim

#endif  //AUTO_AIM__YOLOV5_HPP