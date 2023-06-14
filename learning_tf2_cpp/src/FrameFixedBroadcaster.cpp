#include "../include/learning_tf2_cpp/FrameFixedBroadcaster.hpp"

FrameFixedBroadcaster::FrameFixedBroadcaster(): Node("fixed_frame_tf2_broadcaster")
{
  tf_broadcaster_ = std::make_shared<tf2_ros::TransformBroadcaster>(this);
  timer_ = this->create_wall_timer(100ms, std::bind(&FrameFixedBroadcaster::BroadcastTimerCallback, this));
}

void FrameFixedBroadcaster::BroadcastTimerCallback()
{
  geometry_msgs::msg::TransformStamped t;
  t.header.stamp = this->get_clock()->now();
  t.header.frame_id = "turtle1";
  t.child_frame_id = "carrot1";
  t.transform.translation.x = 0.0;
  t.transform.translation.y = 2.0;
  t.transform.translation.z = 0.0;
  t.transform.rotation.x = 0.0;
  t.transform.rotation.y = 0.0;
  t.transform.rotation.z = 0.0;
  t.transform.rotation.w = 1.0;
  tf_broadcaster_->sendTransform(t);
}