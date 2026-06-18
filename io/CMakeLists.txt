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

target_link_libraries(io MvCameraControl MVSDK usb-1.0 yaml-cpp serial)

################## 检查 ROS 环境 ##################
find_package(ament_cmake QUIET)
find_package(rclcpp QUIET)
find_package(std_msgs QUIET)
find_package(sensor_msgs QUIET)
find_package(cv_bridge QUIET)
find_package(geometry_msgs QUIET)
find_package(tf2_ros QUIET)           # 添加 tf2_ros
find_package(tf2_geometry_msgs QUIET) # 添加 tf2_geometry_msgs
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

    # 设置 ROS2 依赖（添加 tf2_ros 和 tf2_geometry_msgs）
    include_directories(${std_msgs_INCLUDE_DIRS} ${sensor_msgs_INCLUDE_DIRS} ${cv_bridge_INCLUDE_DIRS})
    ament_target_dependencies(io 
        rclcpp 
        std_msgs 
        sensor_msgs 
        cv_bridge 
        rm_interfaces 
        geometry_msgs 
        tf2_ros           # 添加
        tf2_geometry_msgs # 添加
        tf2               # 添加核心 tf2 库
    )
endif()