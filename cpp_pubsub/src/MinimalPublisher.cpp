#include "../include/cpp_pubsub/MinimalPublisher.hpp"

MinimalPublisher::MinimalPublisher(): Node("minimal_publisher"), count_(0)
{
#ifndef CUSTOM_INTERFACES_SWITCH_ON
  publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
#else
  publisher_ = this->create_publisher<interfaces_tutorial::msg::Num>("topic", 10);
#endif

  timer_ = this->create_wall_timer(500ms, std::bind(&MinimalPublisher::TimerCallback, this));
}

void MinimalPublisher::TimerCallback(void)
{
#ifndef CUSTOM_INTERFACES_SWITCH_ON
  auto message = std_msgs::msg::String();
  message.data = "Hello, world! " + std::to_string(count_++);
  RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
#else
    auto message = interfaces_tutorial::msg::Num();         
    message.num = this->count_++;
    RCLCPP_INFO(this->get_logger(), "Publishing: '%d'", message.num);
#endif

  publisher_->publish(message);
}