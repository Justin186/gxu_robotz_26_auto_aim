cmake_minimum_required(VERSION 3.16)

find_package(yaml-cpp REQUIRED)

add_subdirectory(serial)

# 创建目标 io
add_library(io STATIC 
    hikrobot/hikrobot.cpp    
    mindvision/mindvision.cpp  
    usbcamera/usbcamera.cpp  
    camera.cpp
    cboard.cpp
    dm_imu/dm_imu.cpp
    gimbal/gimbal.cpp
    xrobot_imu/xrobot_imu.cpp
    sim_imu/sim_imu.cpp
    shm_ipc/shm_adapter.cpp  # 添加共享内存适配器
)

# hikrobot
target_include_directories(io PUBLIC hikrobot/include)
if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
  target_link_directories(io PUBLIC hikrobot/lib/amd64)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64")
  target_link_directories(io PUBLIC hikrobot/lib/arm64)
else()
  message(FATAL_ERROR "Unsupported architecture: ${CMAKE_HOST_SYSTEM_PROCESSOR}!")
endif()

# mindvision
target_include_directories(io PUBLIC mindvision/include)
if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
  target_link_directories(io PUBLIC mindvision/lib/amd64)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64")
  target_link_directories(io PUBLIC mindvision/lib/arm64)
else()
  message(FATAL_ERROR "Unsupported architecture: ${CMAKE_HOST_SYSTEM_PROCESSOR}!")
endif()

target_link_libraries(io MvCameraControl MVSDK usb-1.0 yaml-cpp serial pthread)

################## 检查 ROS 环境 ##################
find_package(ament_cmake QUIET)
find_package(rclcpp QUIET)
find_package(std_msgs QUIET)
find_package(sensor_msgs QUIET)
find_package(cv_bridge QUIET)
find_package(geometry_msgs QUIET)
find_package(tf2_ros QUIET)
find_package(tf2_geometry_msgs QUIET)
find_package(rosidl_typesupport_cpp QUIET)

set(rm_interfaces_DIR ${CMAKE_SOURCE_DIR}/rm_interfaces/share/rm_interfaces/cmake)
find_package(rm_interfaces QUIET)

# 如果找不到 ROS 环境，则跳过 ROS 相关的部分
if(NOT ament_cmake_FOUND OR NOT rclcpp_FOUND OR NOT std_msgs_FOUND OR NOT rosidl_typesupport_cpp_FOUND OR NOT rm_interfaces_FOUND OR NOT geometry_msgs_FOUND OR NOT sensor_msgs_FOUND OR NOT cv_bridge_FOUND OR NOT tf2_ros_FOUND OR NOT tf2_geometry_msgs_FOUND)
    message(WARNING "ROS2 not found, skipping ROS2 specific code.")
else()
    message(STATUS "ROS2 environment found, compiling ROS2-related code.")
    
    # 添加 ROS2 相关的文件
    target_sources(io PRIVATE ros2/publish2sim.cpp ros2/subscribe2sim.cpp)

    # 设置 ROS2 依赖
    include_directories(${std_msgs_INCLUDE_DIRS} ${sensor_msgs_INCLUDE_DIRS} ${cv_bridge_INCLUDE_DIRS})
    ament_target_dependencies(io 
        rclcpp 
        std_msgs 
        sensor_msgs 
        cv_bridge 
        rm_interfaces 
        geometry_msgs 
        tf2_ros
        tf2_geometry_msgs
        tf2
    )
endif()

################## 共享内存 IPC（独立于 ROS2） ##################
# 共享内存 IPC 总是编译，不依赖 ROS2
target_include_directories(io PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}           # 让 shm_ipc 能找到头文件
    ${CMAKE_CURRENT_SOURCE_DIR}/shm_ipc   # 显式包含 shm_ipc 目录
)

# 检查 C++20 或 C++23 支持（<expected> 需要 C++23）
include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-std=c++23" COMPILER_SUPPORTS_CXX23)
if(COMPILER_SUPPORTS_CXX23)
    target_compile_options(io PRIVATE -std=c++23)
    message(STATUS "Using C++23 for shared memory IPC")
else()
    message(WARNING "C++23 not supported, shared memory IPC may not compile")
endif()

# 添加 OpenCV 依赖（如果还没有）
find_package(OpenCV REQUIRED)
target_link_libraries(io ${OpenCV_LIBS})