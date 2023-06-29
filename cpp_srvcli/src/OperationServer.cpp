#include "../include/cpp_srvcli/OperationServer.hpp"

#ifndef CUSTOM_INTERFACES_SWITCH_ON
void OperationServer_Handle(const std::shared_ptr<rmw_request_id_t> request_header,
         const std::shared_ptr<example_interfaces::srv::AddTwoInts::Request> request,
         const std::shared_ptr<example_interfaces::srv::AddTwoInts::Response> response)
{
  (void)request_header;
  response->sum = request->a + request->b;
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Incoming request\n a: %ld" " b: %ld",request->a, request->b);
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "sending back response: [%ld]", (long int)response->sum);
}
#else
void OperationServer_Handle(const std::shared_ptr<rmw_request_id_t> request_header,
         const std::shared_ptr<interfaces_tutorial::srv::AddThreeInts::Request> request,
         const std::shared_ptr<interfaces_tutorial::srv::AddThreeInts::Response> response)
{
  (void)request_header;
  response->sum = request->a + request->b + request->c;
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Incoming request\n a: %ld" " b: %ld" " c: %ld",request->a, request->b, request->c);
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "sending back response: [%ld]", (long int)response->sum);
}
#endif
