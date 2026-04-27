#ifndef AUTO_AIM__TRT_INFER_HPP
#define AUTO_AIM__TRT_INFER_HPP

#include <NvInfer.h>
#include <NvOnnxParser.h>
#include <string>
#include <vector>
#include <memory>
#include <cstddef>
#include <cstdint>
#include <cuda_runtime_api.h>
#if NV_TENSORRT_MAJOR >= 10
#include <NvInferRuntime.h>
#endif

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
  void infer(const float* input_data, float* output_data,
             int input_w, int input_h, int input_c, int output_size);
  void infer(const uint16_t* input_data, float* output_data,
             int input_w, int input_h, int input_c, int output_size);
  void infer(const uint16_t* input_data, uint16_t* output_data,
             int input_w, int input_h, int input_c, int output_size);
  bool output_is_fp16() const { return output_dtype_ == nvinfer1::DataType::kHALF; }

private:
  void build_from_onnx(const std::string& onnx_path);
  void load_engine(const std::string& engine_path);
  size_t get_data_type_size(nvinfer1::DataType type) const;
  void convert_fp32_to_fp16(const float* src, void* dst, size_t count) const;
  void convert_fp16_to_fp32(const void* src, float* dst, size_t count) const;
  void ensure_io_initialized(size_t input_count, size_t output_count);
  
  TRTLogger logger_;
  std::unique_ptr<nvinfer1::IRuntime> runtime_;
  std::unique_ptr<nvinfer1::ICudaEngine> engine_;
  std::unique_ptr<nvinfer1::IExecutionContext> context_;
  cudaStream_t stream_;
  
  void* buffers_[2];
  size_t input_bytes_;
  size_t output_bytes_;
  nvinfer1::DataType input_dtype_;
  nvinfer1::DataType output_dtype_;
  int input_index_;
  int output_index_;
  std::vector<float> input_fp32_buffer_;
  std::vector<uint16_t> input_fp16_buffer_;
  std::vector<uint16_t> output_fp16_buffer_;
  void* host_input_staging_;
  void* host_output_staging_;
  bool io_bound_;
#if NV_TENSORRT_MAJOR >= 10
  std::string input_tensor_name_;
  std::string output_tensor_name_;
#endif
};

} // namespace auto_aim

#endif // AUTO_AIM__TRT_INFER_HPP
