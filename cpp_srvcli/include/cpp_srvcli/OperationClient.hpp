#ifndef OPERATION_CLIENT_HPP
#define OPERATION_CLIENT_HPP
#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

#include <memory>

void OperationClient_Do(const std::shared_ptr<rclcpp::Node>& node,
                        const rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedPtr& client,
                        const std::shared_ptr<example_interfaces::srv::AddTwoInts_Request>& request);

#endif