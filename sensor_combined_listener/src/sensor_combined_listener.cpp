#include <iostream>
#include "rclcpp/rclcpp.hpp"
#include "px4_msgs/msg/sensor_combined.hpp"

struct Listener : public rclcpp::Node{
    Listener() : Node("listener"){
        subscription_ = this->create_subscription<px4_msgs::msg::SensorCombined>("sensor_combined_topic",
            [](px4_msgs::msg::SensorCombined::UniquePtr msg) {
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
        });
    }
private:
    rclcpp::Subscription<px4_msgs::msg::SensorCombined>::SharedPtr subscription_;
};

int main(int argc, char *argv[])
{
    std::cout << "Starting demo..." << std::endl;
    fflush(stdout);
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Listener>());
    return 0;
}
