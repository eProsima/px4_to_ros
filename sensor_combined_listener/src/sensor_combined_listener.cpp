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
    PX4Receiver() : Node("px4_receiver"){
        //publisher_ = this->create_publisher<px4_msgs::msg::SensorCombined>("latency_measurement_topic");
        subscription_ = this->create_subscription<px4_msgs::msg::SensorCombined>("sensor_combined_topic",
            [&](px4_msgs::msg::SensorCombined::UniquePtr msg) {
            std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
            std::cout << "RECEIVED DATA ON SENSOR COMBINED" << std::endl;
            std::cout << "================================" << std::endl;
            std::cout << "gyro_rad[0]: " << msg->gyro_rad[0] << std::endl;
            std::cout << "gyro_rad[1]: " << msg->gyro_rad[1] << std::endl;
            std::cout << "gyro_rad[2]: " << msg->gyro_rad[2] << std::endl;
            std::cout << "gyro_integral_dt: " << msg->gyro_integral_dt << std::endl;
            std::cout << "accelerometer_timestamp_relative: " << msg->accelerometer_timestamp_relative << std::endl;
            std::cout << "accelerometer_m_s2[0]: " << msg->accelerometer_m_s2[0] << std::endl;
            std::cout << "accelerometer_m_s2[1]: " << msg->accelerometer_m_s2[1] << std::endl;
            std::cout << "accelerometer_m_s2[2]: " << msg->accelerometer_m_s2[2] << std::endl;
            std::cout << "accelerometer_integral_dt: " << msg->accelerometer_integral_dt << std::endl;
            std::cout << "magnetometer_timestamp_relative: " << msg->magnetometer_timestamp_relative << std::endl;
            std::cout << "magnetometer_ga[0]: " << msg->magnetometer_ga[0] << std::endl;
            std::cout << "magnetometer_ga[1]: " << msg->magnetometer_ga[1] << std::endl;
            std::cout << "magnetometer_ga[2]: " << msg->magnetometer_ga[2] << std::endl;
            std::cout << "baro_timestamp_relative: " << msg->baro_timestamp_relative << std::endl;
            std::cout << "baro_alt_meter: " << msg->baro_alt_meter << std::endl;
            std::cout << "baro_temp_celcius: " << msg->baro_temp_celcius << std::endl;
            fflush(stdout);
            //publisher_->publish(msg);
        });
    }
private:
    //rclcpp::Publisher<px4_msgs::msg::SensorCombined>::SharedPtr publisher_;
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
