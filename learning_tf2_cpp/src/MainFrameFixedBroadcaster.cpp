#include "rclcpp/rclcpp.hpp"
#include "../include/learning_tf2_cpp/FrameFixedBroadcaster.hpp"

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<FrameFixedBroadcaster>());
  rclcpp::shutdown();
  return 0;
}