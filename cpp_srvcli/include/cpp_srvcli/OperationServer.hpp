#ifndef OPERATION_SERVER_HPP
#define OPERATION_SERVER_HPP
#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

#include <memory>

void OperationServer_Handle(const std::shared_ptr<rmw_request_id_t> request_header,
         const std::shared_ptr<example_interfaces::srv::AddTwoInts::Request> request,
         const std::shared_ptr<example_interfaces::srv::AddTwoInts::Response> response);

#endif