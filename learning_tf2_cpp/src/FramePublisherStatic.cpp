#include <memory>
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "../include/learning_tf2_cpp/FramePublisherStatic.hpp"

FramePublisherStatic::FramePublisherStatic(char * transformation[]): Node("static_turtle_tf2_broadcaster")
{
  tf_static_broadcaster_ = std::make_shared<tf2_ros::StaticTransformBroadcaster>(this);  
  // Publish static transforms once at startup
  this->MakeTransforms(transformation);
}

void FramePublisherStatic::MakeTransforms(char * transformation[])
{
  geometry_msgs::msg::TransformStamped t;
  t.header.stamp = this->get_clock()->now();
  t.header.frame_id = "world";
  t.child_frame_id = transformation[1];
  t.transform.translation.x = atof(transformation[2]);
  t.transform.translation.y = atof(transformation[3]);
  t.transform.translation.z = atof(transformation[4]);
  tf2::Quaternion q;
  q.setRPY(
    atof(transformation[5]),
    atof(transformation[6]),
    atof(transformation[7]));
  t.transform.rotation.x = q.x();
  t.transform.rotation.y = q.y();
  t.transform.rotation.z = q.z();
  t.transform.rotation.w = q.w();
  tf_static_broadcaster_->sendTransform(t);
}