#include "../include/cpp_pubsub/MinimalSubscriberStatistics.hpp"

MinimalSubscriberStatistics::MinimalSubscriberStatistics(): Node("minimal_subscriber_with_topic_statistics")
{
  // manually enable topic statistics via options
  auto options = rclcpp::SubscriptionOptions();
  options.topic_stats_options.state = rclcpp::TopicStatisticsState::Enable;
  
  // configure the collection window and publish period (default 1s)
  options.topic_stats_options.publish_period = std::chrono::seconds(10);
  
  // configure the topic name (default '/statistics')
  // options.topic_stats_options.publish_topic = "/topic_statistics"
  
  // lamda expression
  auto callback = [this](std_msgs::msg::String::SharedPtr msg) 
                  {
                     this->TopicCallback(msg);
                  };
  
  subscription_ = this->create_subscription<std_msgs::msg::String>("topic", 10, callback, options);
}

void MinimalSubscriberStatistics::TopicCallback(const std_msgs::msg::String::SharedPtr msg) const
{
  RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg->data.c_str());
}