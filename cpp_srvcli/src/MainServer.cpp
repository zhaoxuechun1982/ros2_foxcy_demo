#include "../include/cpp_srvcli/InterfacesConfig.h"
#include "../include/cpp_srvcli/OperationServer.hpp"


int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

#ifndef CUSTOM_INTERFACES_SWITCH_ON
  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("add_2_ints_server");

  rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr service = node->create_service<example_interfaces::srv::AddTwoInts>("add_2_ints", &OperationServer_Handle);

  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to add 2 ints.");
#else
  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("add_3_ints_server");

  rclcpp::Service<interfaces_tutorial::srv::AddThreeInts>::SharedPtr service = node->create_service<interfaces_tutorial::srv::AddThreeInts>("add_3_ints", &OperationServer_Handle);

  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to add 3 ints.");
#endif

  rclcpp::spin(node);
  rclcpp::shutdown();
}