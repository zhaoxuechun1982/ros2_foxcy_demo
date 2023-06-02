#include "../include/bag_recorder/BagRecorder.hpp"

BagRecorder::BagRecorder(): Node("bag_recorder")
{
  const rosbag2_cpp::StorageOptions storage_options({"my_bag", "sqlite3"});
  const rosbag2_cpp::ConverterOptions converter_options({rmw_get_serialization_format(),rmw_get_serialization_format()});
  writer_ = std::make_unique<rosbag2_cpp::writers::SequentialWriter>();
  writer_->open(storage_options, converter_options);
  writer_->create_topic({"chatter", "std_msgs/msg/String", rmw_get_serialization_format(), ""});
  subscription_ = create_subscription<std_msgs::msg::String>("chatter", 10, std::bind(&BagRecorder::TopicCallback, this, _1));
}

void BagRecorder::TopicCallback(RCLCPP_SERIALIZED_MESSAGE_T msg) const
{
  auto bag_message = std::make_shared<rosbag2_storage::SerializedBagMessage>();
  bag_message->serialized_data = std::shared_ptr<rcutils_uint8_array_t>(
    new rcutils_uint8_array_t,
    // lamda function 
    [this](rcutils_uint8_array_t *msg) 
    {
      auto fini_return = rcutils_uint8_array_fini(msg);
      delete msg;
      if (fini_return != RCUTILS_RET_OK) 
      {
        RCLCPP_ERROR(get_logger(), "Failed to destroy serialized message %s", rcutils_get_error_string().str);
      }
    }
    );
  *bag_message->serialized_data = msg->release_rcl_serialized_message();
  bag_message->topic_name = "chatter";
  if (rcutils_system_time_now(&bag_message->time_stamp) != RCUTILS_RET_OK) 
  {
    RCLCPP_ERROR(get_logger(), "Error getting current time: %s", rcutils_get_error_string().str);
  }
  writer_->write(bag_message);
}