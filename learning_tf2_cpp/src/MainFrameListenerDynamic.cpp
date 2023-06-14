#include "rclcpp/rclcpp.hpp"
#include "../include/learning_tf2_cpp/FrameListenerDynamic.hpp"

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<FrameListenerDynamic>());
  rclcpp::shutdown();
  return 0;
}