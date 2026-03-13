#include "target.hpp"

#include <numeric>

#include "tools/logger.hpp"
#include "tools/math_tools.hpp"

namespace auto_aim
{
Target::Target(
  const Armor & armor, std::chrono::steady_clock::time_point t, double radius, int armor_num,
  Eigen::VectorXd P0_dig)
: name(armor.name),
  armor_type(armor.type),
  jumped(false),
  last_id(0),
  update_count_(0),
  armor_num_(armor_num),
  t_(t),
  is_switch_(false),
  is_converged_(false),
  switch_count_(0)
{
  auto r = radius;
  priority = armor.priority;
  const Eigen::VectorXd & xyz = armor.xyz_in_world;
  const Eigen::VectorXd & ypr = armor.ypr_in_world;

  // 世界坐标系下的车的旋转中心的坐标
  auto center_x = xyz[0] + r * std::cos(ypr[0]);
  auto center_y = xyz[1] + r * std::sin(ypr[0]);
  auto center_z = xyz[2];

  // 索引  变量  描述
  // 0     x    旋转中心x坐标
  // 1     vx   旋转中心x速度
  // 2     y    旋转中心y坐标  
  // 3     vy   旋转中心y速度
  // 4     z    旋转中心z坐标
  // 5     vz   旋转中心z速度
  // 6     a    车身朝向角度（yaw）/ 最开始观测到的装甲板朝向
  // 7     w    车身角速度
  // 8     r    基准旋转半径
  // 9     l    长短轴差（r2 - r1）
  // 10    h    z方向高度差（z2 - z1）

  // x0: 初始状态预测量 P0: 初始估计误差协方差矩阵（反映当前状态估计的不确定性与各维度相关性）
  Eigen::VectorXd x0{{center_x, 0, center_y, 0, center_z, 0, ypr[0], 0, r, 0, 0}};  //初始化预测量
  Eigen::MatrixXd P0 = P0_dig.asDiagonal(); // 使用各兵种预定的P0对角线参数初始化估计误差协方差矩阵，这里只是对角线上有值，说明各状态量之间假设不相关

  // 防止夹角求和出现异常值
  auto x_add = [](const Eigen::VectorXd & a, const Eigen::VectorXd & b) -> Eigen::VectorXd {
    Eigen::VectorXd c = a + b;
    c[6] = tools::limit_rad(c[6]);
    return c;
  };

  ekf_ = tools::ExtendedKalmanFilter(x0, P0, x_add);  // 初始化滤波器（预测量、预测量协方差）
}

Target::Target(double x, double vyaw, double radius, double h) : armor_num_(4) // 人为初始化目标，好像是初期测试用的，现在应该用不上
{
  Eigen::VectorXd x0{{x, 0, 0, 0, 0, 0, 0, vyaw, radius, 0, h}};
  Eigen::VectorXd P0_dig{{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  Eigen::MatrixXd P0 = P0_dig.asDiagonal();

  // 防止夹角求和出现异常值
  auto x_add = [](const Eigen::VectorXd & a, const Eigen::VectorXd & b) -> Eigen::VectorXd {
    Eigen::VectorXd c = a + b;
    c[6] = tools::limit_rad(c[6]);
    return c;
  };

  ekf_ = tools::ExtendedKalmanFilter(x0, P0, x_add);  //初始化滤波器（预测量、预测量协方差）
}

void Target::predict(std::chrono::steady_clock::time_point t) // EKF中的第一大步：预测
{
  auto dt = tools::delta_time(t, t_); // 当前时间与上次执行预测时间的差值
  predict(dt);
  t_ = t; // 更新时间
}

void Target::predict(double dt) // 感觉这两个重载函数完全可以写在一起，没必要搞两个，不过写成包装函数也有它的道理
{
  // 状态转移雅可比矩阵（对应书上的A）（即A_k，是f(^x_(k-1),0)对x_(k-1)（这里指状态向量）偏导的雅可比矩阵，例如对第一行，是x_k分别对x_(k-1),vx_(k-1)...的偏导）
  // 例如(0,1)位置，表示x_k=x_(k-1)+dt*vx_(k-1)对vx_(k-1)的偏导，等于dt
  // 值得一提的是，由于我们的状态方程是线性的（因为短时间内视为匀速模型，而加速度带来的影响放在了过程噪声中），所以状态转移雅可比矩阵A直接就是状态转移矩阵F本身（因为对于线性系统f(x)=Fx,∂f/∂x=∂(Fx)/∂x=F），所以变量名用F也是合情合理的
  // clang-format off
  Eigen::MatrixXd F{
    {1, dt,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    {0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    {0,  0,  1, dt,  0,  0,  0,  0,  0,  0,  0},
    {0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0},
    {0,  0,  0,  0,  1, dt,  0,  0,  0,  0,  0},
    {0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0},
    {0,  0,  0,  0,  0,  0,  1, dt,  0,  0,  0},
    {0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0},
    {0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0},
    {0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0},
    {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1}
  };
  // clang-format on

  // Piecewise White Noise Model
  // https://github.com/rlabbe/Kalman-and-Bayesian-Filters-in-Python/blob/master/07-Kalman-Filter-Math.ipynb
  // 这里提到的分段白噪声模型中"分段"指的是认为噪声在每个Δt内恒定，对应的是连续白噪声模型，认为噪声在整个时间连续变化
  // 之所以选择分段模型，是因为求Q矩阵只需简单矩阵乘法，但是连续的话需要积分，形式更复杂
  double v1, v2; // 根据目标不同设定不同方差基准，但这不是分段白噪声模型的分段的含义
  if (name == ArmorName::outpost) {
    v1 = 10;   // 前哨站加速度方差
    v2 = 0.1;  // 前哨站角加速度方差
  } else {
    v1 = 100;  // 加速度方差
    v2 = 400;  // 角加速度方差
  }
  // 根据上面提到的分段白噪声模型，下面这些系数不再是以前我们认为的经验值，而是通过实实在在的数学推导得出的
  // 原英文文献不易理解，具体可以看AI总结的推导过程：https://chat.deepseek.com/share/xxbd6uiqyqv6wlbdms
  auto a = dt * dt * dt * dt / 4;
  auto b = dt * dt * dt / 2;
  auto c = dt * dt;
  // 过程噪声协方差矩阵Q
  // clang-format off
  Eigen::MatrixXd Q{
    {a * v1, b * v1,      0,      0,      0,      0,      0,      0, 0, 0, 0},
    {b * v1, c * v1,      0,      0,      0,      0,      0,      0, 0, 0, 0},
    {     0,      0, a * v1, b * v1,      0,      0,      0,      0, 0, 0, 0},
    {     0,      0, b * v1, c * v1,      0,      0,      0,      0, 0, 0, 0},
    {     0,      0,      0,      0, a * v1, b * v1,      0,      0, 0, 0, 0},
    {     0,      0,      0,      0, b * v1, c * v1,      0,      0, 0, 0, 0},
    {     0,      0,      0,      0,      0,      0, a * v2, b * v2, 0, 0, 0},
    {     0,      0,      0,      0,      0,      0, b * v2, c * v2, 0, 0, 0},
    {     0,      0,      0,      0,      0,      0,      0,      0, 0, 0, 0},
    {     0,      0,      0,      0,      0,      0,      0,      0, 0, 0, 0},
    {     0,      0,      0,      0,      0,      0,      0,      0, 0, 0, 0}
  };
  // clang-format on

  // 防止夹角求和出现异常值
  auto f = [&](const Eigen::VectorXd & x) -> Eigen::VectorXd {
    Eigen::VectorXd x_prior = F * x;
    x_prior[6] = tools::limit_rad(x_prior[6]);
    return x_prior;
  };

  // 前哨站转速特判
  // 如果当前对象已经收敛，并且是前哨站目标，并且角速度超过2rad/s，那么将角速度限制在2.51rad/s（大约等于144度/s）
  // 这么做的原因是前哨站有固定的旋转速度，需要更多更新（更新次数超过10次）来准确估计这个固定值，收敛后强制执行这个约束
  if (this->convergened() && this->name == ArmorName::outpost && std::abs(this->ekf_.x[7]) > 2)
    this->ekf_.x[7] = this->ekf_.x[7] > 0 ? 2.51 : -2.51;

  ekf_.predict(F, Q, f); // 送进EKF进行预测
}

void Target::update(const Armor & armor) // EKF中的第二大步：更新
{
  // 装甲板匹配
  // 由于tracker中始终是对一个target进行跟踪，所以一旦target在set_target中被初始化，就确定了这个target对应了车上的哪块装甲板，因此在后续观测到车上的其他装甲板时，需要进行匹配
  int id;
  auto min_angle_error = 1e10; // 初始化一个很大的角度误差
  const std::vector<Eigen::Vector4d> & xyza_list = armor_xyza_list(); // 计算出所有装甲板的坐标和朝向

  std::vector<std::pair<Eigen::Vector4d, int>> xyza_i_list;
  for (int i = 0; i < armor_num_; i++) {
    xyza_i_list.push_back({xyza_list[i], i}); // 将装甲板坐标和对应id打包存储，感觉这里后续可以优化（因为明明armor_xyza_list()就可以返回带有id的列表），虽然性能提升可能微乎其微，但还是希望代码能简洁些
  }

  std::sort( // 根据distance对装甲板进行排序，distance越小的排在前面
    xyza_i_list.begin(), xyza_i_list.end(),
    [](const std::pair<Eigen::Vector4d, int> & a, const std::pair<Eigen::Vector4d, int> & b) {
      Eigen::Vector3d ypd1 = tools::xyz2ypd(a.first.head(3)); // 计算出需要用于比较的distance
      Eigen::Vector3d ypd2 = tools::xyz2ypd(b.first.head(3)); // 感觉这里也可以优化，因为也计算了不需要的yaw和pitch
      return ypd1[2] < ypd2[2];
    });

  // 取前3个distance最小的装甲板，计算它们与观测值的角度误差，选择误差最小的作为匹配的装甲板
  for (int i = 0; i < 3; i++) {
    const auto & xyza = xyza_i_list[i].first;
    Eigen::Vector3d ypd = tools::xyz2ypd(xyza.head(3));
    // 计算装甲板朝向误差和观测方向（装甲板相对于相机的yaw角）误差的总和
    auto angle_error = std::abs(tools::limit_rad(armor.ypr_in_world[0] - xyza[3])) +
                       std::abs(tools::limit_rad(armor.ypd_in_world[0] - ypd[0]));

    if (std::abs(angle_error) < std::abs(min_angle_error)) {
      id = xyza_i_list[i].second;
      min_angle_error = angle_error;
    }
  }

  if (id != 0) jumped = true;

  if (id != last_id) {
    is_switch_ = true;
  } else {
    is_switch_ = false;
  }

  if (is_switch_) switch_count_++;

  last_id = id;
  update_count_++;

  update_ypda(armor, id);
}

void Target::update_ypda(const Armor & armor, int id)
{
  // 同济并没有采用更新xyza的方法，而是选择ypda为观测量进行更新，因为这更符合测量本质，而且yaw/pitch误差几乎独立于距离，如果使用xyz，距离误差会线性放大到x,y误差
  // 获取观测雅可比矩阵H
  Eigen::MatrixXd H = h_jacobian(ekf_.x, id);
  // Eigen::VectorXd R_dig{{4e-3, 4e-3, 1, 9e-2}};
  auto center_yaw = std::atan2(armor.xyz_in_world[1], armor.xyz_in_world[0]); // 计算车身朝向
  auto delta_angle = tools::limit_rad(armor.ypr_in_world[0] - center_yaw); // 装甲板朝向与车身朝向的夹角
  // 算出观测噪声协方差矩阵R的对角线元素
  Eigen::VectorXd R_dig{
      {4e-3,  // 固定yaw噪声
      4e-2,  // 固定pitch噪声
      log(std::abs(delta_angle) + 1) + 1,  // 自适应距离噪声：当装甲板不在正对时（delta_angle大），距离估计不准，增大噪声
      log(std::abs(armor.ypd_in_world[2]) + 1) / 200 + 9e-2}};  // 自适应角度噪声：距离越远，角度估计越不准

  // 观测噪声协方差矩阵R
  Eigen::MatrixXd R = R_dig.asDiagonal();

  // 定义非线性观测函数h，将状态量x映射到观测量z(ypda)
  // 观测函数描述了给定的状态x下，理论上应该观测到什么数据
  auto h = [&](const Eigen::VectorXd & x) -> Eigen::Vector4d {
    Eigen::VectorXd xyz = h_armor_xyz(x, id);
    Eigen::VectorXd ypd = tools::xyz2ypd(xyz);
    auto angle = tools::limit_rad(x[6] + id * 2 * CV_PI / armor_num_);
    return {ypd[0], ypd[1], ypd[2], angle};
  };

  // 防止夹角求差出现异常值
  auto z_subtract = [](const Eigen::VectorXd & a, const Eigen::VectorXd & b) -> Eigen::VectorXd {
    Eigen::VectorXd c = a - b;
    c[0] = tools::limit_rad(c[0]);
    c[1] = tools::limit_rad(c[1]);
    c[3] = tools::limit_rad(c[3]);
    return c;
  };

  const Eigen::VectorXd & ypd = armor.ypd_in_world;
  const Eigen::VectorXd & ypr = armor.ypr_in_world;
  Eigen::VectorXd z{{ypd[0], ypd[1], ypd[2], ypr[0]}};  //获得观测量

  // 计算预测值和观测值的残差 (Innovation)
  Eigen::VectorXd z_predict = h(ekf_.x);
  Eigen::VectorXd residual = z_subtract(z, z_predict);
  
  // 核心逻辑：如果预测的角度 (yaw) 或距离误差异常大，说明目标发生了不可预测的机动（如急速换向）
  // 此时惩罚滤波器，增大状态协方差矩阵P中与速度和位置相关的对角线元素，让其重新快速收敛到最新观测
  if (std::abs(residual[0]) > 0.08 || std::abs(residual[1]) > 0.08) { 
    // 角度残差大于约4.5度，或者距离残差过大
    // 主动为 x, vx, y, vy, z, vz 的协方差增加不确定性
    ekf_.P.diagonal()[0] += 0.05;  // x
    ekf_.P.diagonal()[1] += 5.0;   // vx
    ekf_.P.diagonal()[2] += 0.05;  // y
    ekf_.P.diagonal()[3] += 5.0;   // vy
    ekf_.P.diagonal()[4] += 0.05;  // z
    ekf_.P.diagonal()[5] += 5.0;   // vz
    tools::logger()->warn("[Target] Target Manuevering Detected! Residual yaw: {:.3f}", residual[0]);
  }

  ekf_.update(z, H, R, h, z_subtract); // 送进EKF进行更新
}

Eigen::VectorXd Target::ekf_x() const { return ekf_.x; }

const tools::ExtendedKalmanFilter & Target::ekf() const { return ekf_; }

std::vector<Eigen::Vector4d> Target::armor_xyza_list() const // 以最开始观测到的那块装甲板为基准，计算出所有装甲板的坐标和朝向
{
  std::vector<Eigen::Vector4d> _armor_xyza_list;

  for (int i = 0; i < armor_num_; i++) {
    auto angle = tools::limit_rad(ekf_.x[6] + i * 2 * CV_PI / armor_num_);
    Eigen::Vector3d xyz = h_armor_xyz(ekf_.x, i); // 计算出每个装甲板的中心坐标
    _armor_xyza_list.push_back({xyz[0], xyz[1], xyz[2], angle});
  }
  return _armor_xyza_list;
}

bool Target::diverged() const // 判断是否发散：滤波器估计的状态偏离真实状态，或者估计变得不稳定
{
  // 通过检查滤波器估计的两个旋转半径是否在合理范围内（0.05到0.5米之间）来判断是否发散
  auto r_ok = ekf_.x[8] > 0.05 && ekf_.x[8] < 0.5; // 短轴半径r1
  auto l_ok = ekf_.x[8] + ekf_.x[9] > 0.05 && ekf_.x[8] + ekf_.x[9] < 0.5; // 长轴半径r2，说是l其实判断的也是旋转半径

  if (r_ok && l_ok) return false;

  tools::logger()->debug("[Target] r={:.3f}, l={:.3f}", ekf_.x[8], ekf_.x[9]);
  return true;
}

bool Target::convergened() // 判断是否收敛：滤波器估计的状态逐渐接近真实状态，不确定性（协方差）减小
{
  // 1. is_converged作为私有变量在构造函数的初始化列表中被初始化为false
  // 2. 如果不是前哨站目标，且更新次数超过3次且没有发散，标记为收敛
  // 3. 如果是前哨站目标，且更新次数超过10次且没有发散，标记为收敛
  // 4. 返回收敛状态
  if (this->name != ArmorName::outpost && update_count_ > 3 && !this->diverged()) {
    is_converged_ = true;
  }

  //前哨站特殊判断
  if (this->name == ArmorName::outpost && update_count_ > 10 && !this->diverged()) {
    is_converged_ = true;
  }

  return is_converged_;
}

Eigen::Vector3d Target::h_armor_xyz(const Eigen::VectorXd & x, int id) const
{
  // 计算第id个装甲板中心在世界坐标系中的坐标
  // id用于区分不同的装甲板，id=0时表示最开始观测到的装甲板，id=1表示逆时针旋转90度/120度(2π/armor_num_)后的装甲板，依此类推
  auto angle = tools::limit_rad(x[6] + id * 2 * CV_PI / armor_num_);
  auto use_l_h = (armor_num_ == 4) && (id == 1 || id == 3); // 这里不知道为什么只判断4号步兵，按理说是车的话长短轴都不一样

  auto r = (use_l_h) ? x[8] + x[9] : x[8];
  auto armor_x = x[0] - r * std::cos(angle);
  auto armor_y = x[2] - r * std::sin(angle);
  auto armor_z = (use_l_h) ? x[4] + x[10] : x[4];

  return {armor_x, armor_y, armor_z};
}

Eigen::MatrixXd Target::h_jacobian(const Eigen::VectorXd & x, int id) const
{
  // 计算观测函数h对状态量x的雅可比矩阵H
  // 先算H_armor_xyza[∂(xyza)/∂状态]，再算H_armor_ypda[∂(ypda)/∂(xyza)]，最后相乘得到真正的H_ypda（链式法则）
  auto angle = tools::limit_rad(x[6] + id * 2 * CV_PI / armor_num_);
  auto use_l_h = (armor_num_ == 4) && (id == 1 || id == 3);

  auto r = (use_l_h) ? x[8] + x[9] : x[8];
  auto dx_da = r * std::sin(angle);
  auto dy_da = -r * std::cos(angle);

  auto dx_dr = -std::cos(angle);
  auto dy_dr = -std::sin(angle);
  auto dx_dl = (use_l_h) ? -std::cos(angle) : 0.0;
  auto dy_dl = (use_l_h) ? -std::sin(angle) : 0.0;

  auto dz_dh = (use_l_h) ? 1.0 : 0.0;

  // clang-format off
  Eigen::MatrixXd H_armor_xyza{
    {1, 0, 0, 0, 0, 0, dx_da, 0, dx_dr, dx_dl,     0}, // ∂x/∂状态
    {0, 0, 1, 0, 0, 0, dy_da, 0, dy_dr, dy_dl,     0}, // ∂y/∂状态
    {0, 0, 0, 0, 1, 0,     0, 0,     0,     0, dz_dh}, // ∂z/∂状态
    {0, 0, 0, 0, 0, 0,     1, 0,     0,     0,     0}  // ∂a/∂状态
  };
  // clang-format on

  Eigen::VectorXd armor_xyz = h_armor_xyz(x, id);
  Eigen::MatrixXd H_armor_ypd = tools::xyz2ypd_jacobian(armor_xyz);
  // clang-format off
  Eigen::MatrixXd H_armor_ypda{
    {H_armor_ypd(0, 0), H_armor_ypd(0, 1), H_armor_ypd(0, 2), 0},
    {H_armor_ypd(1, 0), H_armor_ypd(1, 1), H_armor_ypd(1, 2), 0},
    {H_armor_ypd(2, 0), H_armor_ypd(2, 1), H_armor_ypd(2, 2), 0},
    {                0,                 0,                 0, 1}
  };
  // clang-format on

  return H_armor_ypda * H_armor_xyza;
}

bool Target::checkinit() { return isinit; }

}  // namespace auto_aim
