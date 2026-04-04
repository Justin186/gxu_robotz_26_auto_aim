# 广西大学ROBOT-Z战队26赛季自瞄算法

本项目为广西大学ROBOT-Z战队2026赛季自瞄算法的开源仓库，基于25赛季同济大学SuperPower战队自瞄框架sp_vision_25进行开发和优化。
原项目仓库地址：https://github.com/TongjiSuperPower/sp_vision_25

## 项目环境
操作系统：Ubuntu 22.04\
运算平台：NUC12WSKI7（i7-1260P，16GB）\
相机型号：海康MV-CS016-10UC\
镜头型号：海康官方6mm镜头\
下位机型号：RoboMaster开发板C型（STM32F407）\
IMU型号：使用C板内置BMI088作为IMU\
通信方式：MicroUSB虚拟串口\
辅助工具：NoMachine（远程桌面）、PlotJuggler（绘制曲线图）

## 编译方式
1. 安装依赖项：
   - [MindVision SDK](https://mindvision.com.cn/category/software/sdk-installation-package/)或[HikRobot SDK](https://www.hikrobotics.com/cn2/source/support/software/MVS_STD_GML_V2.1.2_231116.zip)
   - [OpenVINO](https://docs.openvino.ai/2024/get-started/install-openvino/install-openvino-archive-linux.html)
   - [Ceres](http://ceres-solver.org/installation.html)
   - 其余：
    ```bash
    sudo apt install -y \
        git \
        g++ \
        cmake \
        can-utils \
        libopencv-dev \
        libfmt-dev \
        libeigen3-dev \
        libspdlog-dev \
        libyaml-cpp-dev \
        libusb-1.0-0-dev \
        nlohmann-json3-dev \
        openssh-server \
        screen \
        pkg-config \
        libgstreamer1.0-dev \
        libgstreamer-plugins-base1.0-dev \
        gstreamer1.0-tools \
        gstreamer1.0-plugins-base \
        gstreamer1.0-plugins-good \
        gstreamer1.0-plugins-ugly \
        gstreamer1.0-plugins-bad
    ```

2. 编译：
    ```bash
    cmake -B build
    make -C build/ -j`nproc`
    ```

3. 运行demo:
    ```bash
    ./build/auto_aim_test
    ```

4. 注册自启：
    1. 确保已安装`screen`:
        ```
        sudo apt install screen
        ```
    2. 创建`.desktop`文件:
        ```
        mkdir ~/.config/autostart/
        touch ~/.config/autostart/sp_vision.desktop
        ```
    3. 在该文件中写入:
        ```
        [Desktop Entry]
        Type=Application
        Exec=/home/rm/Desktop/sp_vision_25/autostart.sh
        Name=sp_vision
        ```
        注: [Exec](https://specifications.freedesktop.org/desktop-entry-spec/desktop-entry-spec-latest.html)必须为绝对路径.
    4. 确保`autostart.sh`有可执行权限:
        ```
        chmod +x autostart.sh
        ```

5. USB2CAN设置（可选）
    1. 创建`.rules`文件:
        ```
        sudo touch /etc/udev/rules.d/99-can-up.rules
        ```
    2. 在该文件中写入:
        ```
        ACTION=="add", KERNEL=="can0", RUN+="/sbin/ip link set can0 up type can bitrate 1000000"
        ACTION=="add", KERNEL=="can1", RUN+="/sbin/ip link set can1 up type can bitrate 1000000"

6. 使用GPU推理（可选）
    ```
    mkdir neo  
    cd neo  

    wget https://github.com/intel/intel-graphics-compiler/releases/download/igc-1.0.13463.18/intel-igc-core_1.0.13463.18_amd64.deb  
    wget https://github.com/intel/intel-graphics-compiler/releases/download/igc-1.0.13463.18/intel-igc-opencl_1.0.13463.18_amd64.deb  
    wget https://github.com/intel/compute-runtime/releases/download/23.09.25812.14/intel-level-zero-gpu-dbgsym_1.3.25812.14_amd64.ddeb  
    wget https://github.com/intel/compute-runtime/releases/download/23.09.25812.14/intel-level-zero-gpu_1.3.25812.14_amd64.deb  
    wget https://github.com/intel/compute-runtime/releases/download/23.09.25812.14/intel-opencl-icd-dbgsym_23.09.25812.14_amd64.ddeb  
    wget https://github.com/intel/compute-runtime/releases/download/23.09.25812.14/intel-opencl-icd_23.09.25812.14_amd64.deb  
    wget https://github.com/intel/compute-runtime/releases/download/23.09.25812.14/libigdgmm12_22.3.0_amd64.deb  
    wget https://github.com/intel/compute-runtime/releases/download/23.09.25812.14/ww09.sum  

    sha256sum -c ww09.sum  
    sudo dpkg -i *.deb  
    ```
    注：如果使用 GPU 异步推理（async-infer），最高显示分辨率限制为 1920×1080 (24Hz)

7. 串口设置
    1. 授予权限
        ```
        sudo usermod -a -G dialout $USER
        ```
    2. 获取端口 ID（serial, idVendor, idProduct）
        ```
        udevadm info -a -n /dev/ttyACM0 | grep -E '({serial}|{idVendor}|{idProduct})'
        ```
        将 /dev/ttyACM0 替换为实际设备名。
    3. 创建 udev 规则文件
        ```
        sudo touch /etc/udev/rules.d/99-usb-serial.rules
        ```
        然后在文件中写入如下内容（用真实 ID 替换示例，SYMLINK 是规则应用后固定的串口名）：
        ```
        SUBSYSTEM=="tty", ATTRS{idVendor}=="1234", ATTRS{idProduct}=="1234", ATTRS{serial}=="A1234567", SYMLINK+="gimbal"
        ```
    4. 重新加载 udev 规则
        ```
        sudo udevadm control --reload-rules
        sudo udevadm trigger
        ```
    5. 检查结果
        ```
        ls -l /dev/gimbal
        # Expected output (example):
        # lrwxrwxrwx 1 root root 7 Jul 21 10:00 /dev/gimbal -> ttyACM0
        ```