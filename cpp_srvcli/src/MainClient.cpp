#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"
#include "../include/cpp_srvcli/OperationClient.hpp"
#include "../include/cpp_srvcli/InterfacesConfig.h"

#include <chrono>
#include <cstdlib>
#include <memory>

using namespace std::chrono_literals;

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

#ifndef CUSTOM_INTERFACES_SWITCH_ON
  if (argc != 3) 
  {
      RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "usage: add_2_ints_client X Y");
      return 1;
  }

  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("add_2_ints_client");
  rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedPtr client = node->create_client<example_interfaces::srv::AddTwoInts>("add_2_ints");

  auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
  request->a = atoll(argv[1]);
  request->b = atoll(argv[2]);

  while (!client->wait_for_service(1s)) 
  {
    if (!rclcpp::ok()) 
    {
      RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
      return 0;
    }
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
  }
#else
  if (argc != 4) 
  {
      RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "usage: add_3_ints_client X Y Z");
      return 1;
  }

  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("add_3_ints_client");
  rclcpp::Client<interfaces_tutorial::srv::AddThreeInts>::SharedPtr client = node->create_client<interfaces_tutorial::srv::AddThreeInts>("add_3_ints");

  auto request = std::make_shared<interfaces_tutorial::srv::AddThreeInts::Request>();
  request->a = atoll(argv[1]);
  request->b = atoll(argv[2]);
  request->c = atoll(argv[3]);

  while (!client->wait_for_service(1s)) 
  {
    if (!rclcpp::ok()) 
    {
      RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
      return 0;
    }
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
  }
#endif

  OperationClient_Handle(node, client, request);

  rclcpp::shutdown();
  return 0;
}