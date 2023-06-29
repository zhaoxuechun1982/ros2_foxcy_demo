#include "../include/cpp_pubsub/MinimalSubscriber.hpp"

MinimalSubscriber::MinimalSubscriber(): Node("minimal_subscriber")
{
#ifndef CUSTOM_INTERFACES_SWITCH_ON
  subscription_ = this->create_subscription<std_msgs::msg::String>("topic", 10, std::bind(&MinimalSubscriber::TopicCallback, this, _1));
#else
  subscription_ = this->create_subscription<interfaces_tutorial::msg::Num>("topic", 10, std::bind(&MinimalSubscriber::TopicCallback, this, _1));
#endif
}

#ifndef CUSTOM_INTERFACES_SWITCH_ON
void MinimalSubscriber::TopicCallback(const std_msgs::msg::String::SharedPtr msg) const
{
  RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg->data.c_str());
}
#else
void MinimalSubscriber::TopicCallback(const interfaces_tutorial::msg::Num::SharedPtr msg) const
{
  RCLCPP_INFO(this->get_logger(), "I heard: '%d'", msg->num);
}
#endif