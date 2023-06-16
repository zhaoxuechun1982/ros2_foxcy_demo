#include "rclcpp/rclcpp.hpp"
#include "../include/learning_tf2_cpp/FrameListenerDynamic.hpp"

FrameListenerDynamic::FrameListenerDynamic(): Node("turtle_tf2_frame_listener"), turtle_spawning_service_ready_(false), turtle_spawned_(false)
{
  // Declare and acquire `target_frame` parameter
  target_frame_ = this->declare_parameter<std::string>("target_frame", "turtle1");
  tf_buffer_ = std::make_unique<tf2_ros::Buffer>(this->get_clock());
  tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);
  // Create a client to spawn a turtle
  spawner_ = this->create_client<turtlesim::srv::Spawn>("spawn");
  // Create turtle2 velocity publisher
  publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("turtle2/cmd_vel", 1);
  // Call on_timer function every second
  timer_ = this->create_wall_timer(1s, std::bind(&FrameListenerDynamic::OnTimer, this));
}

void FrameListenerDynamic::OnTimer()
{
  // Store frame names in variables that will be used to
  // compute transformations
  std::string fromFrameRel = target_frame_.c_str();
  std::string toFrameRel = "turtle2";
  
  if (turtle_spawning_service_ready_) 
  {
    if (turtle_spawned_) 
    {
      geometry_msgs::msg::TransformStamped t;
      // Look up for the transformation between target_frame and turtle2 frames
      // and send velocity commands for turtle2 to reach target_frame
      try 
      {
        //t = tf_buffer_->lookupTransform(toFrameRel, fromFrameRel, tf2::TimePointZero);

        // Demo of using time
        rclcpp::Time now = this->get_clock()->now();
        t = tf_buffer_->lookupTransform(toFrameRel, fromFrameRel, now);
        //t = tf_buffer_->lookupTransform(toFrameRel, fromFrameRel, now, 50ms);
        
        // Demo of traveling in time
        //rclcpp::Time now = this->get_clock()->now();
        //rclcpp::Time when = now - rclcpp::Duration(5, 0);
        //t = tf_buffer_->lookupTransform(toFrameRel, now, fromFrameRel, when, "world", 50ms);
      } 
      catch (const tf2::TransformException & ex) 
      {
        RCLCPP_INFO(this->get_logger(), "Could not transform %s to %s: %s", toFrameRel.c_str(), fromFrameRel.c_str(), ex.what());
        return;
      }
      geometry_msgs::msg::Twist msg;
      static const double scaleRotationRate = 1.0;
      msg.angular.z = scaleRotationRate * atan2(t.transform.translation.y, t.transform.translation.x);
      static const double scaleForwardSpeed = 0.5;
      msg.linear.x = scaleForwardSpeed * sqrt(pow(t.transform.translation.x, 2) + pow(t.transform.translation.y, 2));
      publisher_->publish(msg);
    } 
    else 
    {
      RCLCPP_INFO(this->get_logger(), "Successfully spawned");
      turtle_spawned_ = true;
    }
  } 
  else 
  {
    // Check if the service is ready
    if (spawner_->service_is_ready()) 
    {
      // Initialize request with turtle name and coordinates
      // Note that x, y and theta are defined as floats in turtlesim/srv/Spawn
      auto request = std::make_shared<turtlesim::srv::Spawn::Request>();
      request->name = "turtle2";
      request->x = 4.0;
      request->y = 2.0;
      request->theta = 0.0;
      // Call request
      using ServiceResponseFuture = rclcpp::Client<turtlesim::srv::Spawn>::SharedFuture;
      auto response_received_callback = [this](ServiceResponseFuture future) 
      {
        auto result = future.get();
        if (strcmp(result->name.c_str(), "turtle2") == 0) 
        {
          turtle_spawning_service_ready_ = true;
        } 
        else 
        {
          RCLCPP_ERROR(this->get_logger(), "Service callback result mismatch");
        }
      };
      auto result = spawner_->async_send_request(request, response_received_callback);
    } 
    else
    {
      RCLCPP_INFO(this->get_logger(), "Service is not ready");
    }
  }
}