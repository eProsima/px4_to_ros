// Copyright 2015 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <string>

// include ROS 1
#ifdef __clang__
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunused-parameter"
#endif
#include "ros/ros.h"
#ifdef __clang__
# pragma clang diagnostic pop
#endif

// include ROS 2
#include "rclcpp/rclcpp.hpp"

#include "ros1_bridge/bridge.hpp"


int main(int argc, char * argv[])
{
  // ROS 1 node
  ros::init(argc, argv, "ros_bridge");
  ros::NodeHandle ros1_node, ros1_node2;

  // ROS 2 node
  rclcpp::init(argc, argv);
  auto ros2_node = rclcpp::node::Node::make_shared("ros_bridge");
  auto ros2_node2 = rclcpp::node::Node::make_shared("ros_bridge2");

  // bridge one example topic
  std::string topic_name = "sensor_combined_topic";
  std::string topic_name_back = "sensor_combined_topic_back";
  std::string ros1_type_name = "px4_msgs/SensorCombined";
  std::string ros2_type_name = "px4_msgs/SensorCombined";
  size_t queue_size = 10;

  auto handles = ros1_bridge::create_bidirectional_bridge(
    ros1_node, ros2_node, ros1_type_name, ros2_type_name, topic_name, queue_size);

  auto handles2 = ros1_bridge::create_bidirectional_bridge(
    ros1_node2, ros2_node2, ros1_type_name, ros2_type_name, topic_name_back, queue_size);

  // ROS 1 asynchronous spinner
  ros::AsyncSpinner async_spinner(1);
  async_spinner.start();

  // ROS 2 spinning loop
  rclcpp::executors::SingleThreadedExecutor executor;
  while (ros1_node.ok() && ros1_node2.ok() && rclcpp::utilities::ok()) {
    executor.spin_node_once(ros2_node, std::chrono::milliseconds(1000));
    executor.spin_node_once(ros2_node2, std::chrono::milliseconds(1000));
  }

  return 0;
}
