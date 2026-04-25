#include "trt_infer.hpp"

#include <fstream>
#include <iostream>
#include <vector>
#include <filesystem>
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
  size_t input_size = input_w * input_h * input_c * sizeof(float);
  size_t output_bytes = output_size * sizeof(float);

  if (buffers_[0] == nullptr) {
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
    cudaMalloc(&buffers_[0], input_size);
    cudaMalloc(&buffers_[1], output_bytes);
#else
      input_index_ = 0; // Default to 0 for input
      for (int i = 0; i < engine_->getNbBindings(); ++i) {
          if (engine_->bindingIsInput(i)) {
              input_index_ = i;
              break;
          }
      }
      output_index_ = 1 - input_index_;
      cudaMalloc(&buffers_[input_index_], input_size);
      cudaMalloc(&buffers_[output_index_], output_bytes);
#endif
  }

#if NV_TENSORRT_MAJOR >= 10
  nvinfer1::Dims4 input_shape{1, input_c, input_h, input_w};
  context_->setInputShape(input_tensor_name_.c_str(), input_shape);
  context_->setTensorAddress(input_tensor_name_.c_str(), buffers_[0]);
  context_->setTensorAddress(output_tensor_name_.c_str(), buffers_[1]);
  cudaMemcpyAsync(buffers_[0], input_data.data(), input_size, cudaMemcpyHostToDevice, stream_);
  context_->enqueueV3(stream_);
  cudaMemcpyAsync(output_data.data(), buffers_[1], output_bytes, cudaMemcpyDeviceToHost, stream_);
#else
  cudaMemcpyAsync(buffers_[input_index_], input_data.data(), input_size, cudaMemcpyHostToDevice, stream_);
  context_->enqueueV2(buffers_, stream_, nullptr);
  cudaMemcpyAsync(output_data.data(), buffers_[output_index_], output_bytes, cudaMemcpyDeviceToHost, stream_);
#endif
  cudaStreamSynchronize(stream_);
}

} // namespace auto_aim
