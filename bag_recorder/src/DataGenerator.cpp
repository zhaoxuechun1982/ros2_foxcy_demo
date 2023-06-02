#include "../include/bag_recorder/DataGenerator.hpp"

DataGenerator::DataGenerator(): Node("data_generator")
{
  data.data = 0;
  const rosbag2_cpp::StorageOptions storage_options({"timed_synthetic_bag", "sqlite3"});
  const rosbag2_cpp::ConverterOptions converter_options({rmw_get_serialization_format(), rmw_get_serialization_format()});
  writer_ = std::make_unique<rosbag2_cpp::writers::SequentialWriter>();
  writer_->open(storage_options, converter_options);
  writer_->create_topic({"synthetic", "example_interfaces/msg/Int32", rmw_get_serialization_format(), ""});
  timer_ = create_wall_timer(1s, std::bind(&DataGenerator::TimerCallback, this));
}

void DataGenerator::TimerCallback()
{
  auto serializer = rclcpp::Serialization<example_interfaces::msg::Int32>();
  auto serialized_message = rclcpp::SerializedMessage();
  serializer.serialize_message(&data, &serialized_message);

  auto bag_message = std::make_shared<rosbag2_storage::SerializedBagMessage>();

  bag_message->serialized_data = std::shared_ptr<rcutils_uint8_array_t>(
    new rcutils_uint8_array_t,
    [this](rcutils_uint8_array_t *msg) {
      auto fini_return = rcutils_uint8_array_fini(msg);
      delete msg;
      if (fini_return != RCUTILS_RET_OK) 
      {
        RCLCPP_ERROR(get_logger(), "Failed to destroy serialized message %s", rcutils_get_error_string().str);
      }
    });
  *bag_message->serialized_data = serialized_message.release_rcl_serialized_message();

  bag_message->topic_name = "synthetic";
  if (rcutils_system_time_now(&bag_message->time_stamp) != RCUTILS_RET_OK) 
  {
    RCLCPP_ERROR(get_logger(), "Error getting current time: %s",rcutils_get_error_string().str);
  }

  writer_->write(bag_message);
  ++data.data;
}