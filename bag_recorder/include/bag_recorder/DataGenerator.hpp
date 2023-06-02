#include <chrono>

#include <example_interfaces/msg/int32.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/serialization.hpp>

#include <rosbag2_cpp/writer.hpp>
#include <rosbag2_cpp/writers/sequential_writer.hpp>
#include <rosbag2_storage/serialized_bag_message.hpp>

using namespace std::chrono_literals;

class DataGenerator : public rclcpp::Node
{
public:
  DataGenerator();

private:
using RCLCPP_TIMERBASE_T = rclcpp::TimerBase::SharedPtr;
using RCLCPP_ROS2BAG_SEQUENTIAL_WRITER_T = std::unique_ptr<rosbag2_cpp::writers::SequentialWriter>;
using EXAMPLE_INTERFACES_MSG_INT32_T = example_interfaces::msg::Int32;
  void TimerCallback();
  RCLCPP_TIMERBASE_T timer_;
  RCLCPP_ROS2BAG_SEQUENTIAL_WRITER_T writer_;
  EXAMPLE_INTERFACES_MSG_INT32_T data;
};