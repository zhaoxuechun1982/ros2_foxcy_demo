#include "../include/cpp_srvcli/OperationServer.hpp"

void OperationServer_Handle(const std::shared_ptr<rmw_request_id_t> request_header,
         const std::shared_ptr<example_interfaces::srv::AddTwoInts::Request> request,
         const std::shared_ptr<example_interfaces::srv::AddTwoInts::Response> response)
{
  (void)request_header;
  response->sum = request->a + request->b;
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Incoming request\n a: %ld" " b: %ld",request->a, request->b);
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "sending back response: [%ld]", (long int)response->sum);
}
