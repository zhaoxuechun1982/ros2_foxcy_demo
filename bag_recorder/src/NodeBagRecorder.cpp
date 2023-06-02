#include "../include/bag_recorder/BagRecorder.hpp"

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<BagRecorder>());
  rclcpp::shutdown();
  
  return 0;
}