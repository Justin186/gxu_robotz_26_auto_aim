#ifndef AUTO_AIM__TRT_INFER_HPP
#define AUTO_AIM__TRT_INFER_HPP

#include <NvInfer.h>
#include <NvOnnxParser.h>
#include <string>
#include <vector>
#include <memory>
#include <cuda_runtime_api.h>

namespace auto_aim
{

class TRTLogger : public nvinfer1::ILogger
{
public:
  void log(Severity severity, const char* msg) noexcept override;
};

class TRTInfer
{
public:
  TRTInfer(const std::string& model_path);
  ~TRTInfer();

  void infer(const std::vector<float>& input_data, std::vector<float>& output_data, 
             int input_w, int input_h, int input_c, int output_size);

private:
  void build_from_onnx(const std::string& onnx_path);
  void load_engine(const std::string& engine_path);
  
  TRTLogger logger_;
  std::unique_ptr<nvinfer1::IRuntime> runtime_;
  std::unique_ptr<nvinfer1::ICudaEngine> engine_;
  std::unique_ptr<nvinfer1::IExecutionContext> context_;
  cudaStream_t stream_;
  
  void* buffers_[2];
  int input_index_;
  int output_index_;
};

} // namespace auto_aim

#endif // AUTO_AIM__TRT_INFER_HPP
