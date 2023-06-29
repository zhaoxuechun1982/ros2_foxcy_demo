#include "../include/cpp_srvcli/OperationClient.hpp"

#ifndef CUSTOM_INTERFACES_SWITCH_ON
void OperationClient_Handle(const std::shared_ptr<rclcpp::Node>& node,
                        const rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedPtr& client,
                        const std::shared_ptr<example_interfaces::srv::AddTwoInts_Request>& request)
{
  auto result = client->async_send_request(request);

  // Wait for the result.
  if (rclcpp::spin_until_future_complete(node, result) == rclcpp::FutureReturnCode::SUCCESS)
  {
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Sum: %ld", result.get()->sum);
  } 
  else 
  {
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service add_2_ints");
  }
}
#else
void OperationClient_Handle(const std::shared_ptr<rclcpp::Node>& node,
                        const rclcpp::Client<interfaces_tutorial::srv::AddThreeInts>::SharedPtr& client,
                        const std::shared_ptr<interfaces_tutorial::srv::AddThreeInts_Request>& request)
{
  auto result = client->async_send_request(request);

  // Wait for the result.
  if (rclcpp::spin_until_future_complete(node, result) == rclcpp::FutureReturnCode::SUCCESS)
  {
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Sum: %ld", result.get()->sum);
  } 
  else 
  {
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service add_3_ints");
  }
}
#endif