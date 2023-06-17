#include "rclcpp/rclcpp.hpp"
#include "../include/learning_tf2_cpp/PointStampedListener.hpp"

PointStampedListener::PointStampedListener() : Node("turtle_tf2_pose_drawer")
{
  // Declare and acquire `target_frame` parameter
  target_frame_ = this->declare_parameter<std::string>("target_frame", "turtle1");

  std::chrono::duration<int> buffer_timeout(1);

  tf2_buffer_ = std::make_shared<tf2_ros::Buffer>(this->get_clock());
  // Create the timer interface before call to waitForTransform,
  // to avoid a tf2_ros::CreateTimerInterfaceException exception
  auto timer_interface = std::make_shared<tf2_ros::CreateTimerROS>(
    this->get_node_base_interface(),
    this->get_node_timers_interface());
    tf2_buffer_->setCreateTimerInterface(timer_interface);
    tf2_listener_ =std::make_shared<tf2_ros::TransformListener>(*tf2_buffer_);

  point_sub_.subscribe(this, "/turtle3/turtle_point_stamped");
  tf2_filter_ = std::make_shared<tf2_ros::MessageFilter<geometry_msgs::msg::PointStamped>>(
    point_sub_, *tf2_buffer_, target_frame_, 100, this->get_node_logging_interface(),
    this->get_node_clock_interface(), buffer_timeout);
  // Register a callback with tf2_ros::MessageFilter to be called when transforms are available
  tf2_filter_->registerCallback(&PointStampedListener::MsgCallback, this);
}

void PointStampedListener::MsgCallback(const geometry_msgs::msg::PointStamped::SharedPtr point_ptr)
{
  geometry_msgs::msg::PointStamped point_out;
  try 
  {
    tf2_buffer_->transform(*point_ptr, point_out, target_frame_);
    RCLCPP_INFO(
      this->get_logger(), "Point of turtle3 in frame of turtle1: x:%f y:%f z:%f\n",
      point_out.point.x,
      point_out.point.y,
      point_out.point.z);
  } catch (const tf2::TransformException & ex) 
  {
    // Print exception which was caught
    RCLCPP_WARN(this->get_logger(), "Failure %s\n", ex.what());
  }
}