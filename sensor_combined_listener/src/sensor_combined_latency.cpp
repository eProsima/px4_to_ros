// Copyright 2017 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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

#include <iostream>
#include "rclcpp/rclcpp.hpp"
#include "px4_msgs/msg/sensor_combined.hpp"

struct PX4Receiver : public rclcpp::Node{
    PX4Receiver() : Node("px4_receiver_latency"){
        publisher_ = this->create_publisher<px4_msgs::msg::SensorCombined>("latency_measurement_topic");
        subscription_ = this->create_subscription<px4_msgs::msg::SensorCombined>("sensor_combined_topic",
            [&](px4_msgs::msg::SensorCombined::UniquePtr msg) {
            publisher_->publish(msg);
        });
    }
private:
    rclcpp::Publisher<px4_msgs::msg::SensorCombined>::SharedPtr publisher_;
    rclcpp::Subscription<px4_msgs::msg::SensorCombined>::SharedPtr subscription_;
};

int main(int argc, char *argv[])
{
    std::cout << "Starting demo..." << std::endl;
    fflush(stdout);
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<PX4Receiver>());
    return 0;
}
