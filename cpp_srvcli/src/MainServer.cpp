#include "../include/cpp_srvcli/OperationServer.hpp"

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("add_2_ints_server");

  rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr service = node->create_service<example_interfaces::srv::AddTwoInts>("add_2_ints", &OperationServer_Handle);

  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to add 2 ints.");

  rclcpp::spin(node);
  rclcpp::shutdown();
}