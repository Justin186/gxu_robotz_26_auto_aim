#include "decider.hpp"

#include "perceptron.hpp"

#include <yaml-cpp/yaml.h>

#include <cmath>
#include <opencv2/opencv.hpp>

#include "tools/logger.hpp"
#include "tools/math_tools.hpp"

namespace omniperception
{
Decider::Decider(const std::string & config_path)
{
  // 这里只读取全向决策真正会用到的配置
  auto yaml = YAML::LoadFile(config_path);
  img_width_ = yaml["image_width"].as<double>();
  img_height_ = yaml["image_height"].as<double>();
  new_fov_h_ = yaml["new_fov_h"].as<double>();
  new_fov_v_ = yaml["new_fov_v"].as<double>();
  enemy_color_ =
    (yaml["enemy_color"].as<std::string>() == "red") ? auto_aim::Color::red : auto_aim::Color::blue;
  priority_mode_ = yaml["mode"].as<int>();
  reset();
}

void Decider::reset_runtime_state()
{
  // 切回 tracking / scan 时，清掉扫描和侧向确认的中间状态
  // 左右计数归零，候选结果清空，甩头角度的归零，swithing状态超时计时器归零
  scan_state_ = {};
  left_seen_count_ = 0;
  right_seen_count_ = 0;
  left_candidate_.reset();
  right_candidate_.reset();
  switching_target_yaw_ = 0.0;
  switching_target_pitch_ = 0.0;
  switching_start_time_ = std::chrono::steady_clock::now();
  last_side_detect_time_ = switching_start_time_;
  detect_left_next_ = true;//先从ros相机检测，防止usb延迟大导致
}

void Decider::reset()
{
  reset_runtime_state();
  mode_ = OmniMode::tracking;
}

void Decider::set_mode(OmniMode mode)
{
  if (mode_ == mode) {
    return;
  }

  // tracking / scan 都意味着重新开始一轮状态机
  if (mode == OmniMode::tracking || mode == OmniMode::scan) {
    reset_runtime_state();
  }
  mode_ = mode;
}

Decider::OmniMode Decider::mode() const
{
  return mode_;
}

//全向感知实现，集成侧向感知的所有决策逻辑，返回switching和scan的转向角度
io::Command Decider::decide(
  double current_yaw, double current_pitch, double dt, Perceptron & perceptron)
{
  auto now = std::chrono::steady_clock::now();

  // tracking 模式完全交给主相机闭环，全向层不发命令
  if (mode_ == OmniMode::tracking) {
    return io::Command{false, false, 0, 0};
  }

  // switching 模式只判断是否转到位或超时，不再扫描和侧向识别
  if (mode_ == OmniMode::switching) {
    constexpr double yaw_thresh = 3.0 / 57.3;//切换目标角和当前角的差值小于这个阈值就认为转到位了
    constexpr double pitch_thresh = 3.0 / 57.3;

    //判断是否pitch和yaw都到位
    const bool reached_target =
      std::abs(tools::limit_rad(current_yaw - switching_target_yaw_)) < yaw_thresh &&
      std::abs(current_pitch - switching_target_pitch_) < pitch_thresh;

    if (reached_target) {
      set_mode(OmniMode::scan);//由于第一次进scan后会进入特化扫描，所以不怕因为直接scan而丢失目标
      return io::Command{false, false, 0, 0};
    } else if (now - switching_start_time_ >= switching_timeout_) {
      tools::logger()->info("Switching timeout, back to scan");//超时检测
      set_mode(OmniMode::scan);
      return io::Command{false, false, 0, 0};
    }

    // switching 期间持续发送同一个目标角，保证云台真正转到位
    return io::Command{true, false, switching_target_yaw_, switching_target_pitch_};
  }

  // scan 模式下，按固定间隔轮询左右侧相机
  if (now - last_side_detect_time_ >= side_detect_interval_) {
    last_side_detect_time_ = now;

    DetectionResult result;
    //用于交替检测
    const auto status = detect_left_next_ ? perceptron.detect_left(result)
                                          : perceptron.detect_right(result);
    int & seen_count = detect_left_next_ ? left_seen_count_ : right_seen_count_;
    //更新最优选项
    std::optional<DetectionResult> & candidate =
      detect_left_next_ ? left_candidate_ : right_candidate_;
    
    //DetectStatus三状态，有图无图有目标
    // 没有新帧时，不动计数；否则高频轮询会把低帧率相机误清零
    if (status == DetectStatus::no_frame) {
    //相机有图，并且armors有目标，计加计数+1
    } else if (status == DetectStatus::detected && process_detection(result)) {
      seen_count++;
      candidate = std::move(result);
    } else {
      // 只要拿到了新帧，但新帧里没有有效目标，就认为确认链路中断
      seen_count = 0;
      candidate.reset();
    }

    detect_left_next_ = !detect_left_next_;
  }

  // 左右侧分别累计确认帧数，满足阈值后才允许进入 switching
  auto left_ready = left_seen_count_ >= confirm_count_ ? left_candidate_ : std::nullopt;
  auto right_ready = right_seen_count_ >= confirm_count_ ? right_candidate_ : std::nullopt;
  auto best = choose_switch_candidate(left_ready, right_ready);
  if (best.has_value()) {
    switching_target_yaw_ = tools::limit_rad(current_yaw + best->delta_yaw);
    switching_target_pitch_ = tools::limit_rad(current_pitch + best->delta_pitch);
    switching_start_time_ = now;
    mode_ = OmniMode::switching;

    tools::logger()->info("Switching to {} camera", best->source);
    return io::Command{true, false, switching_target_yaw_, switching_target_pitch_};
  }

  auto scan_result = scan(current_yaw, dt);
  return io::Command{true, false, scan_result.yaw, scan_result.pitch};
}

//scan下，对侧向进行是否有目标的判断，有就先排序后给出转向角度
bool Decider::process_detection(DetectionResult & result) const
{
  // Perceptron 只负责给原始检测，这里再做过滤、优先级和角度换算
  if (armor_filter(result.armors)) return false;

  set_priority(result.armors);  //给每一个目标设置优先级
  sort_armors(result.armors);   //依照先优先级，后图像中心距离排序

  const auto angles = delta_angle(result.armors, result.source);
  result.delta_yaw = angles[0] / 57.3;
  result.delta_pitch = angles[1] / 57.3;
  return true;
}

void Decider::sort_armors(std::list<auto_aim::Armor> & armors) const
{
  // 先看优先级，同优先级时选更靠近图像中心的目标
  const cv::Point2f img_center(img_width_ * 0.5f, img_height_ * 0.5f);
  armors.sort([&img_center](const auto_aim::Armor & a, const auto_aim::Armor & b) {
    if (a.priority != b.priority) {
      return a.priority < b.priority;
    }

    const auto distance_a = cv::norm(a.center - img_center);
    const auto distance_b = cv::norm(b.center - img_center);
    return distance_a < distance_b;
  });
}

std::optional<DetectionResult> Decider::choose_switch_candidate(
  const std::optional<DetectionResult> & left_candidate,
  const std::optional<DetectionResult> & right_candidate) const
{
  // 左右都有候选时：先比优先级，再比回头角绝对值
  if (!left_candidate.has_value()) return right_candidate;
  if (!right_candidate.has_value()) return left_candidate;

  const auto left_priority = left_candidate->armors.front().priority;
  const auto right_priority = right_candidate->armors.front().priority;
  if (left_priority != right_priority) {
    return left_priority < right_priority ? left_candidate : right_candidate;
  }

  return std::abs(left_candidate->delta_yaw) < std::abs(right_candidate->delta_yaw) ? left_candidate
                                                                                     : right_candidate;
}

Decider::ScanResult Decider::omni_scan(double dt)
{
  constexpr double delta_angle = 100.0;
  constexpr double amplitude = 15.0;
  constexpr double period = 0.75;

  scan_state_.scan_cmd_angle += delta_angle * dt;
  const double yaw = tools::limit_rad(scan_state_.scan_cmd_angle / 57.3);
  const double pitch =
    tools::limit_rad(amplitude * std::sin(2 * M_PI * scan_state_.scan_t / period) / 57.3 - 0.15);

  scan_state_.scan_t += dt;
  if (scan_state_.scan_t >= period) scan_state_.scan_t -= period;

  return {yaw, pitch};
}

Decider::ScanResult Decider::short_lost_scan(double start_yaw_deg, double dt)
{
  constexpr double yaw_amplitude = 20.0;
  constexpr double yaw_period = 1.0;
  constexpr double pitch_amplitude = 1.0;
  constexpr double pitch_period = 0.2;

  scan_state_.scan_t += dt;
  if (scan_state_.scan_t >= 4.0) {
    scan_state_.use_omni_scan = true;
  }

  const double yaw_deg =
    start_yaw_deg - yaw_amplitude * std::sin(2 * M_PI * scan_state_.scan_t / yaw_period);
  const double yaw = tools::limit_rad(yaw_deg / 57.3);
  const double pitch = tools::limit_rad(
    pitch_amplitude * std::sin(2 * M_PI * scan_state_.scan_t / pitch_period) / 57.3 + 0.1);

  return {yaw, pitch};
}

Decider::ScanResult Decider::scan(double current_yaw, double dt)
{
  // 进入 scan 后，先做一段小范围特化扫描，再切到全向大扫描
  if (scan_state_.scan_t == 0.0 && scan_state_.scan_cmd_angle == 0.0) {
    scan_state_.start_angle = current_yaw * 57.3;
    scan_state_.scan_cmd_angle = scan_state_.start_angle;
    scan_state_.use_omni_scan = false;
  }

  if (scan_state_.use_omni_scan) {
    return omni_scan(dt);
  }
  return short_lost_scan(scan_state_.start_angle, dt);
}

Eigen::Vector2d Decider::delta_angle(
  const std::list<auto_aim::Armor> & armors, const std::string & camera) const
{
  Eigen::Vector2d delta_angle;
  if (camera == "left") {
    delta_angle[0] = 62 + (new_fov_h_ / 2) - armors.front().center_norm.x * new_fov_h_;
    delta_angle[1] = armors.front().center_norm.y * new_fov_v_ - new_fov_v_ / 2;
    return delta_angle;
  }

  delta_angle[0] = -62 + (new_fov_h_ / 2) - armors.front().center_norm.x * new_fov_h_;
  delta_angle[1] = armors.front().center_norm.y * new_fov_v_ - new_fov_v_ / 2;
  return delta_angle;
}

bool Decider::armor_filter(std::list<auto_aim::Armor> & armors) const
{
  if (armors.empty()) return true;

  // 这里只保留当前敌方、非工程、非前哨站、非无敌目标
  armors.remove_if([&](const auto_aim::Armor & a) { return a.color != enemy_color_; });
  armors.remove_if([&](const auto_aim::Armor & a) { return a.name == auto_aim::ArmorName::five; });
  armors.remove_if([&](const auto_aim::Armor & a) { return a.name == auto_aim::ArmorName::outpost; });

  return armors.empty();
}

void Decider::set_priority(std::list<auto_aim::Armor> & armors) const
{
  if (armors.empty()) return;

  const PriorityMap & priority_map = (priority_mode_ == MODE_ONE) ? mode1 : mode2;
  for (auto & armor : armors) {
    armor.priority = priority_map.at(armor.name);
  }
}

}  // namespace omniperception
