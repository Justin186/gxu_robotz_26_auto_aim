#include "mt_detector.hpp"

#include <yaml-cpp/yaml.h>

namespace auto_aim
{
namespace multithread
{

MultiThreadDetector::MultiThreadDetector(const std::string & config_path, bool debug)
: yolo_(config_path, debug)
{
  auto yaml = YAML::LoadFile(config_path);
  auto yolo_name = yaml["yolo_name"].as<std::string>();
  auto model_path = yaml[yolo_name + "_model_path"].as<std::string>();
  device_ = yaml["device"].as<std::string>();

  trt_infer_ = std::make_unique<TRTInfer>(model_path);
  /*
  ov::preprocess::PrePostProcessor ppp(model);
  auto & input = ppp.input();

  input.tensor()
    .set_element_type(ov::element::u8)
    .set_shape({1, 640, 640, 3})  // TODO
    .set_layout("NHWC")
    .set_color_format(ov::preprocess::ColorFormat::BGR);

  input.model().set_layout("NCHW");

  input.preprocess()
    .convert_element_type(ov::element::f32)
    .convert_color(ov::preprocess::ColorFormat::RGB)
    // .resize(ov::preprocess::ResizeAlgorithm::RESIZE_LINEAR)
    .scale(255.0);

  model = ppp.build();
  compiled_model_ = core_.compile_model(
    model, device_, ov::hint::performance_mode(ov::hint::PerformanceMode::THROUGHPUT));
  */

  tools::logger()->info("[MultiThreadDetector] initialized !");
}

void MultiThreadDetector::push(cv::Mat img, std::chrono::steady_clock::time_point t)
{
  auto x_scale = static_cast<double>(640) / img.rows;
  auto y_scale = static_cast<double>(640) / img.cols;
  auto scale = std::min(x_scale, y_scale);
  auto h = static_cast<int>(img.rows * scale);
  auto w = static_cast<int>(img.cols * scale);

  // preproces
  auto input = cv::Mat(640, 640, CV_8UC3, cv::Scalar(0, 0, 0));
  auto roi = cv::Rect(0, 0, w, h);
  cv::resize(img, input(roi), {w, h});

  cv::Mat blob = cv::dnn::blobFromImage(input, 1.0 / 255.0, cv::Size(), cv::Scalar(), true, false);
  std::vector<float> input_data((float*)blob.data, (float*)blob.data + 1 * 3 * 640 * 640);
  
  auto fut = std::make_shared<std::future<std::vector<float>>>(
    std::async(std::launch::async, [this, input_data]() {
      std::lock_guard<std::mutex> lock(infer_mutex_);
      int output_elements = 25200 * 22;
      std::vector<float> output_data(output_elements);
      trt_infer_->infer(input_data, output_data, 640, 640, 3, output_elements);
      return output_data;
    })
  );
  queue_.push({img.clone(), t, fut});
}

std::tuple<std::list<Armor>, std::chrono::steady_clock::time_point> MultiThreadDetector::pop()
{
  auto [img, t, infer_request] = queue_.pop();
  auto output_data = infer_request->get();
  cv::Mat output(25200, 22, CV_32F, output_data.data());
  auto x_scale = static_cast<double>(640) / img.rows;
  auto y_scale = static_cast<double>(640) / img.cols;
  auto scale = std::min(x_scale, y_scale);
  auto armors = yolo_.postprocess(scale, output, img, 0);  //暂不支持ROI

  return {std::move(armors), t};
}

std::tuple<cv::Mat, std::list<Armor>, std::chrono::steady_clock::time_point>
MultiThreadDetector::debug_pop()
{
  auto [img, t, infer_request] = queue_.pop();
  auto output_data = infer_request->get();
  cv::Mat output(25200, 22, CV_32F, output_data.data());
  auto x_scale = static_cast<double>(640) / img.rows;
  auto y_scale = static_cast<double>(640) / img.cols;
  auto scale = std::min(x_scale, y_scale);
  auto armors = yolo_.postprocess(scale, output, img, 0);  //暂不支持ROI

  return {img, std::move(armors), t};
}

}  // namespace multithread

}  // namespace auto_aim
