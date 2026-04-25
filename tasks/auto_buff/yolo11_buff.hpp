#ifndef AUTO_BUFF__YOLO11_BUFF_HPP
#define AUTO_BUFF__YOLO11_BUFF_HPP
#include <yaml-cpp/yaml.h>

#include <filesystem>
#include <opencv2/opencv.hpp>
#include <memory>
#include "tasks/auto_aim/trt_infer.hpp"

#include "tools/logger.hpp"

namespace auto_buff
{
const std::vector<std::string> class_names = {"buff", "r"};

class YOLO11_BUFF
{
public:
  struct Object
  {
    cv::Rect_<float> rect;
    int label;
    float prob;
    std::vector<cv::Point2f> kpt;
  };

  YOLO11_BUFF(const std::string & config);

  // 使用NMS，用来获取多个框
  std::vector<Object> get_multicandidateboxes(cv::Mat & image);

  // 寻找置信度最高的框
  std::vector<Object> get_onecandidatebox(cv::Mat & image);

private:
  std::unique_ptr<auto_aim::TRTInfer> trt_infer_;
  const int NUM_POINTS = 6;

  // 转换图像数据: 先转换元素类型, (可选)然后归一化到[0, 1], (可选)然后交换RB通道
  void convert(
    const cv::Mat & input, cv::Mat & output, const bool normalize, const bool exchangeRB) const;

  // 将image保存为"../result/$${programName}.jpg"
  void save(const std::string & programName, const cv::Mat & image);
};
}  // namespace auto_buff
#endif