#include "../include/cpp_pubsub/MinimalSubscriber.hpp"

MinimalSubscriber::MinimalSubscriber(): Node("minimal_subscriber")
{
  subscription_ = this->create_subscription<std_msgs::msg::String>("topic", 10, std::bind(&MinimalSubscriber::TopicCallback, this, _1));
}

void MinimalSubscriber::TopicCallback(const std_msgs::msg::String::SharedPtr msg) const
{
  RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg->data.c_str());
}