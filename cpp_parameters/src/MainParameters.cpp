#include <rclcpp/rclcpp.hpp>
#include "../include/cpp_parameters/MinimalParameters.hpp"

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalParameters>());
  rclcpp::shutdown();
  return 0;
}