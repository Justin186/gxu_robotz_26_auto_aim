#include "trt_infer.hpp"

#include <fstream>
#include <iostream>
#include <vector>
#include <filesystem>
#include <algorithm>
#include <cstring>
#include <cstdint>
#include "tools/logger.hpp" // Assumed available from context

namespace auto_aim
{

void TRTLogger::log(Severity severity, const char* msg) noexcept {
  if (severity <= Severity::kWARNING) {
   if (tools::logger()) {
     tools::logger()->warn("[TRT] {}", msg);
    } else {
       std::cout << "[TRT] " << msg << std::endl;
    }
  }
}

TRTInfer::TRTInfer(const std::string& model_path) {
  buffers_[0] = nullptr;
  buffers_[1] = nullptr;
  input_bytes_ = 0;
  output_bytes_ = 0;
  input_dtype_ = nvinfer1::DataType::kFLOAT;
  output_dtype_ = nvinfer1::DataType::kFLOAT;
  input_index_ = 0;
  output_index_ = 1;
  cudaStreamCreate(&stream_);
  auto path = std::filesystem::path(model_path);
  if (path.extension() == ".engine" || path.extension() == ".trt") {
    load_engine(model_path);
  } else {
    build_from_onnx(model_path);
  }
}

TRTInfer::~TRTInfer() {
  if (buffers_[0]) cudaFree(buffers_[0]);
  if (buffers_[1]) cudaFree(buffers_[1]);
  cudaStreamDestroy(stream_);
}

void TRTInfer::load_engine(const std::string& engine_path) {
  std::ifstream file(engine_path, std::ios::binary);
  if (!file.good()) throw std::runtime_error("Engine file not found.");
  
  file.seekg(0, std::ios::end);
  size_t size = file.tellg();
  file.seekg(0, std::ios::beg);
  std::vector<char> trt_model_stream(size);
  file.read(trt_model_stream.data(), size);
  file.close();

  runtime_ = std::unique_ptr<nvinfer1::IRuntime>(nvinfer1::createInferRuntime(logger_));
  engine_ = std::unique_ptr<nvinfer1::ICudaEngine>(runtime_->deserializeCudaEngine(trt_model_stream.data(), size));
  context_ = std::unique_ptr<nvinfer1::IExecutionContext>(engine_->createExecutionContext());
}

void TRTInfer::build_from_onnx(const std::string& onnx_path) {
  auto builder = std::unique_ptr<nvinfer1::IBuilder>(nvinfer1::createInferBuilder(logger_));
  auto network = std::unique_ptr<nvinfer1::INetworkDefinition>(builder->createNetworkV2(1U << static_cast<uint32_t>(nvinfer1::NetworkDefinitionCreationFlag::kEXPLICIT_BATCH)));
  auto parser = std::unique_ptr<nvonnxparser::IParser>(nvonnxparser::createParser(*network, logger_));

  if (!parser->parseFromFile(onnx_path.c_str(), static_cast<int>(nvinfer1::ILogger::Severity::kWARNING))) {
    throw std::runtime_error("Failed to parse ONNX model");
  }

  auto config = std::unique_ptr<nvinfer1::IBuilderConfig>(builder->createBuilderConfig());
  config->setFlag(nvinfer1::BuilderFlag::kFP16); // Assuming fp16 is desired
  #if NV_TENSORRT_MAJOR < 8
  config->setMaxWorkspaceSize(1ULL << 30); // 1GB
  builder->setMaxBatchSize(1);
  #else
  config->setMemoryPoolLimit(nvinfer1::MemoryPoolType::kWORKSPACE, 1ULL << 30);
  #endif
  
  auto serialized_engine = std::unique_ptr<nvinfer1::IHostMemory>(builder->buildSerializedNetwork(*network, *config));
  if (!serialized_engine) throw std::runtime_error("Failed to build Engine");

  runtime_ = std::unique_ptr<nvinfer1::IRuntime>(nvinfer1::createInferRuntime(logger_));
  engine_ = std::unique_ptr<nvinfer1::ICudaEngine>(runtime_->deserializeCudaEngine(serialized_engine->data(), serialized_engine->size()));
  context_ = std::unique_ptr<nvinfer1::IExecutionContext>(engine_->createExecutionContext());
}

void TRTInfer::infer(const std::vector<float>& input_data, std::vector<float>& output_data,
                     int input_w, int input_h, int input_c, int output_size) {
  const size_t output_count = static_cast<size_t>(output_size);
  if (output_data.size() < output_count) {
    output_data.resize(output_count);
  }
  infer(input_data.data(), output_data.data(), input_w, input_h, input_c, output_size);
}

void TRTInfer::ensure_io_initialized(size_t input_count, size_t output_count) {
  if (buffers_[0] != nullptr) {
    return;
  }

#if NV_TENSORRT_MAJOR >= 10
  input_index_ = -1;
  output_index_ = -1;
  const int io_count = engine_->getNbIOTensors();
  for (int i = 0; i < io_count; ++i) {
    const char* tensor_name = engine_->getIOTensorName(i);
    if (engine_->getTensorIOMode(tensor_name) == nvinfer1::TensorIOMode::kINPUT) {
      input_index_ = i;
      input_tensor_name_ = tensor_name;
    } else {
      output_index_ = i;
      output_tensor_name_ = tensor_name;
    }
  }
  if (input_index_ < 0 || output_index_ < 0) {
    throw std::runtime_error("Failed to locate TensorRT input/output tensors");
  }
  input_dtype_ = engine_->getTensorDataType(input_tensor_name_.c_str());
  output_dtype_ = engine_->getTensorDataType(output_tensor_name_.c_str());
  input_bytes_ = input_count * get_data_type_size(input_dtype_);
  output_bytes_ = output_count * get_data_type_size(output_dtype_);
  cudaMalloc(&buffers_[0], input_bytes_);
  cudaMalloc(&buffers_[1], output_bytes_);
#else
  input_index_ = 0;
  for (int i = 0; i < engine_->getNbBindings(); ++i) {
    if (engine_->bindingIsInput(i)) {
      input_index_ = i;
      break;
    }
  }
  output_index_ = 1 - input_index_;
  input_dtype_ = engine_->getBindingDataType(input_index_);
  output_dtype_ = engine_->getBindingDataType(output_index_);
  input_bytes_ = input_count * get_data_type_size(input_dtype_);
  output_bytes_ = output_count * get_data_type_size(output_dtype_);
  cudaMalloc(&buffers_[input_index_], input_bytes_);
  cudaMalloc(&buffers_[output_index_], output_bytes_);
#endif
}

void TRTInfer::infer(const float* input_data, float* output_data,
                     int input_w, int input_h, int input_c, int output_size) {
  const size_t input_count = static_cast<size_t>(input_w) * input_h * input_c;
  const size_t output_count = static_cast<size_t>(output_size);
  ensure_io_initialized(input_count, output_count);

  const void* input_host_ptr = input_data;
  if (input_dtype_ == nvinfer1::DataType::kHALF) {
    input_fp16_buffer_.resize(input_count);
    convert_fp32_to_fp16(input_data, input_fp16_buffer_.data(), input_count);
    input_host_ptr = input_fp16_buffer_.data();
  }

  void* output_host_ptr = output_data;
  if (output_dtype_ == nvinfer1::DataType::kHALF) {
    output_fp16_buffer_.resize(output_count);
    output_host_ptr = output_fp16_buffer_.data();
  }

#if NV_TENSORRT_MAJOR >= 10
  nvinfer1::Dims4 input_shape{1, input_c, input_h, input_w};
  context_->setInputShape(input_tensor_name_.c_str(), input_shape);
  context_->setTensorAddress(input_tensor_name_.c_str(), buffers_[0]);
  context_->setTensorAddress(output_tensor_name_.c_str(), buffers_[1]);
  cudaMemcpyAsync(buffers_[0], input_host_ptr, input_bytes_, cudaMemcpyHostToDevice, stream_);
  context_->enqueueV3(stream_);
  cudaMemcpyAsync(output_host_ptr, buffers_[1], output_bytes_, cudaMemcpyDeviceToHost, stream_);
#else
  cudaMemcpyAsync(buffers_[input_index_], input_host_ptr, input_bytes_, cudaMemcpyHostToDevice, stream_);
  context_->enqueueV2(buffers_, stream_, nullptr);
  cudaMemcpyAsync(output_host_ptr, buffers_[output_index_], output_bytes_, cudaMemcpyDeviceToHost, stream_);
#endif
  cudaStreamSynchronize(stream_);

  if (output_dtype_ == nvinfer1::DataType::kHALF) {
    convert_fp16_to_fp32(output_fp16_buffer_.data(), output_data, output_count);
  }
}

void TRTInfer::infer(const uint16_t* input_data, float* output_data,
                     int input_w, int input_h, int input_c, int output_size) {
  const size_t input_count = static_cast<size_t>(input_w) * input_h * input_c;
  const size_t output_count = static_cast<size_t>(output_size);
  ensure_io_initialized(input_count, output_count);

  const void* input_host_ptr = input_data;
  if (input_dtype_ != nvinfer1::DataType::kHALF) {
    input_fp32_buffer_.resize(input_count);
    convert_fp16_to_fp32(input_data, input_fp32_buffer_.data(), input_count);
    input_host_ptr = input_fp32_buffer_.data();
  }

  void* output_host_ptr = output_data;
  if (output_dtype_ == nvinfer1::DataType::kHALF) {
    output_fp16_buffer_.resize(output_count);
    output_host_ptr = output_fp16_buffer_.data();
  }

#if NV_TENSORRT_MAJOR >= 10
  nvinfer1::Dims4 input_shape{1, input_c, input_h, input_w};
  context_->setInputShape(input_tensor_name_.c_str(), input_shape);
  context_->setTensorAddress(input_tensor_name_.c_str(), buffers_[0]);
  context_->setTensorAddress(output_tensor_name_.c_str(), buffers_[1]);
  cudaMemcpyAsync(buffers_[0], input_host_ptr, input_bytes_, cudaMemcpyHostToDevice, stream_);
  context_->enqueueV3(stream_);
  cudaMemcpyAsync(output_host_ptr, buffers_[1], output_bytes_, cudaMemcpyDeviceToHost, stream_);
#else
  cudaMemcpyAsync(buffers_[input_index_], input_host_ptr, input_bytes_, cudaMemcpyHostToDevice, stream_);
  context_->enqueueV2(buffers_, stream_, nullptr);
  cudaMemcpyAsync(output_host_ptr, buffers_[output_index_], output_bytes_, cudaMemcpyDeviceToHost, stream_);
#endif
  cudaStreamSynchronize(stream_);

  if (output_dtype_ == nvinfer1::DataType::kHALF) {
    convert_fp16_to_fp32(output_fp16_buffer_.data(), output_data, output_count);
  }
}

size_t TRTInfer::get_data_type_size(nvinfer1::DataType type) const {
  switch (type) {
    case nvinfer1::DataType::kFLOAT:
      return sizeof(float);
    case nvinfer1::DataType::kHALF:
      return sizeof(uint16_t);
    case nvinfer1::DataType::kINT32:
      return sizeof(int32_t);
#if NV_TENSORRT_MAJOR >= 8
    case nvinfer1::DataType::kBOOL:
      return sizeof(bool);
#endif
    default:
      throw std::runtime_error("Unsupported TensorRT data type");
  }
}

void TRTInfer::convert_fp32_to_fp16(const float* src, void* dst, size_t count) const {
  auto* out = static_cast<uint16_t*>(dst);
  for (size_t i = 0; i < count; ++i) {
    float x = src[i];
    uint32_t bits;
    std::memcpy(&bits, &x, sizeof(float));
    uint32_t sign = (bits >> 16) & 0x8000u;
    uint32_t mantissa = bits & 0x007fffffu;
    int32_t exp = static_cast<int32_t>((bits >> 23) & 0xffu) - 127 + 15;

    if (exp <= 0) {
      if (exp < -10) {
        out[i] = static_cast<uint16_t>(sign);
      } else {
        mantissa = (mantissa | 0x00800000u) >> (1 - exp);
        out[i] = static_cast<uint16_t>(sign | ((mantissa + 0x00001000u) >> 13));
      }
    } else if (exp >= 31) {
      out[i] = static_cast<uint16_t>(sign | 0x7c00u);
    } else {
      out[i] = static_cast<uint16_t>(sign | (static_cast<uint32_t>(exp) << 10) | ((mantissa + 0x00001000u) >> 13));
    }
  }
}

void TRTInfer::convert_fp16_to_fp32(const void* src, float* dst, size_t count) const {
  const auto* in = static_cast<const uint16_t*>(src);
  for (size_t i = 0; i < count; ++i) {
    uint32_t h = in[i];
    uint32_t sign = (h & 0x8000u) << 16;
    uint32_t exp = (h >> 10) & 0x1fu;
    uint32_t mantissa = h & 0x03ffu;
    uint32_t bits;

    if (exp == 0) {
      if (mantissa == 0) {
        bits = sign;
      } else {
        exp = 1;
        while ((mantissa & 0x0400u) == 0) {
          mantissa <<= 1;
          --exp;
        }
        mantissa &= 0x03ffu;
        bits = sign | ((exp + 127 - 15) << 23) | (mantissa << 13);
      }
    } else if (exp == 31) {
      bits = sign | 0x7f800000u | (mantissa << 13);
    } else {
      bits = sign | ((exp + 127 - 15) << 23) | (mantissa << 13);
    }

    std::memcpy(&dst[i], &bits, sizeof(float));
  }
}

} // namespace auto_aim
