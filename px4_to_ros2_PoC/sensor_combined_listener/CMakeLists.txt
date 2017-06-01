cmake_minimum_required(VERSION 3.5)

project(sensor_combined_listener)

find_package(ament_cmake REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -Wpedantic")

find_package(rclcpp REQUIRED)
find_package(px4_msgs REQUIRED)

add_executable(sensor_combined_listener
  src/sensor_combined_listener.cpp)

add_executable(sensor_combined_latency
  src/sensor_combined_latency.cpp)

ament_target_dependencies(sensor_combined_listener
  px4_msgs
  rclcpp)

ament_target_dependencies(sensor_combined_latency
  px4_msgs
  rclcpp)

install(TARGETS
  sensor_combined_listener
  sensor_combined_latency
  DESTINATION bin)

ament_package()
