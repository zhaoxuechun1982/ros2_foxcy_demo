#include "../include/cpp_pubsub/MinimalSubscriberStatistics.hpp"

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriberStatistics>());
  rclcpp::shutdown();
  return 0;
}