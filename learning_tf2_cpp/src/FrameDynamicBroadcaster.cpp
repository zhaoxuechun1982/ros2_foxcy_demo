#include "../include/learning_tf2_cpp/FrameDynamicBroadcaster.hpp"

FrameDynamicBroadcaster::FrameDynamicBroadcaster() : Node("dynamic_frame_tf2_broadcaster")
{
  tf_broadcaster_ = std::make_shared<tf2_ros::TransformBroadcaster>(this);
  timer_ = this->create_wall_timer(100ms, std::bind(&FrameDynamicBroadcaster::BroadcastTimerCallback, this));
}

 void FrameDynamicBroadcaster::BroadcastTimerCallback()
  {
    rclcpp::Time now = this->get_clock()->now();
    double x = now.seconds() * PI;

    geometry_msgs::msg::TransformStamped t;
    t.header.stamp = now;
    t.header.frame_id = "turtle1";
    t.child_frame_id = "carrot1";
    t.transform.translation.x = 10 * sin(x);
    t.transform.translation.y = 10 * cos(x);
    t.transform.translation.z = 0.0;
    t.transform.rotation.x = 0.0;
    t.transform.rotation.y = 0.0;
    t.transform.rotation.z = 0.0;
    t.transform.rotation.w = 1.0;

    tf_broadcaster_->sendTransform(t);
  }  