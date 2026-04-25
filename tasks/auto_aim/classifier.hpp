#ifndef AUTO_AIM__CLASSIFIER_HPP
#define AUTO_AIM__CLASSIFIER_HPP

#include <opencv2/opencv.hpp>
#include <memory>
#include "armor.hpp"
#include "trt_infer.hpp"

namespace auto_aim
{
class Classifier
{
public:
  explicit Classifier(const std::string & config_path);

  void classify(Armor & armor);

  void ovclassify(Armor & armor);

private:
  cv::dnn::Net net_;
  std::unique_ptr<TRTInfer> trt_infer_;
};


}  // namespace auto_aim

#endif  // AUTO_AIM__CLASSIFIER_HPP