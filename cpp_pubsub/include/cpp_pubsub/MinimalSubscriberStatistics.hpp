#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "rclcpp/subscription_options.hpp"

#include "std_msgs/msg/string.hpp"

class MinimalSubscriberStatistics : public rclcpp::Node
{
public:
  MinimalSubscriberStatistics();

private:
  void TopicCallback(const std_msgs::msg::String::SharedPtr msg) const;
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};