#ifndef OMNIPERCEPTION__DETECTION_HPP
#define OMNIPERCEPTION__DETECTION_HPP

#include <chrono>
#include <list>
#include <string>

#include "tasks/auto_aim/armor.hpp"

namespace omniperception
{
//一个识别结果可能包含多个armor,需要排序和过滤。armors, timestamp, delta_yaw, delta_pitch
struct DetectionResult
{
  std::list<auto_aim::Armor> armors;
  std::chrono::steady_clock::time_point timestamp;
  std::string source;  //图像来源左或右
  double delta_yaw;    //rad
  double delta_pitch;  //rad

  DetectionResult() = default;

  DetectionResult(
    std::list<auto_aim::Armor> armors_, std::chrono::steady_clock::time_point timestamp_,
    double delta_yaw_, double delta_pitch_)
  : armors(std::move(armors_)),
    timestamp(timestamp_),
    source(""),
    delta_yaw(delta_yaw_),
    delta_pitch(delta_pitch_)
  {
  }

  DetectionResult(
    std::list<auto_aim::Armor> armors_, std::chrono::steady_clock::time_point timestamp_,
    std::string source_, double delta_yaw_, double delta_pitch_)
  : armors(std::move(armors_)),
    timestamp(timestamp_),
    source(std::move(source_)),
    delta_yaw(delta_yaw_),
    delta_pitch(delta_pitch_)
  {
  }

  // Assignment operator
  DetectionResult & operator=(const DetectionResult & other)
  {
    if (this != &other) {
      armors = other.armors;
      timestamp = other.timestamp;
      source = other.source;
      delta_yaw = other.delta_yaw;
      delta_pitch = other.delta_pitch;
    }
    return *this;
  }
};
}  // namespace omniperception

#endif
