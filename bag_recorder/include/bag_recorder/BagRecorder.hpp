#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

#include <rosbag2_cpp/typesupport_helpers.hpp>
#include <rosbag2_cpp/writer.hpp>
#include <rosbag2_cpp/writers/sequential_writer.hpp>
#include <rosbag2_storage/serialized_bag_message.hpp>

using std::placeholders::_1;

class BagRecorder : public rclcpp::Node
{
public:
  BagRecorder();

private:
using RCLCPP_SERIALIZED_MESSAGE_T = std::shared_ptr<rclcpp::SerializedMessage>;
using RCLCPP_SERIALIZED_MESSAGE_SUBSCRIBER_T = rclcpp::Subscription<rclcpp::SerializedMessage>::SharedPtr;
using RCLCPP_ROS2BAG_SEQUENTIAL_WRITER_T = std::unique_ptr<rosbag2_cpp::writers::SequentialWriter>;
  void TopicCallback(RCLCPP_SERIALIZED_MESSAGE_T msg) const;
  RCLCPP_SERIALIZED_MESSAGE_SUBSCRIBER_T subscription_;
  RCLCPP_ROS2BAG_SEQUENTIAL_WRITER_T writer_;
};