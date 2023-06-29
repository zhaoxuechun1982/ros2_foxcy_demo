#ifndef OPERATION_SERVER_HPP
#define OPERATION_SERVER_HPP
#include "rclcpp/rclcpp.hpp"
#include "InterfacesConfig.h"

#ifndef CUSTOM_INTERFACES_SWITCH_ON
#include "example_interfaces/srv/add_two_ints.hpp"
#else
#include "interfaces_tutorial/srv/add_three_ints.hpp" 
#endif

#include <memory>

#ifndef CUSTOM_INTERFACES_SWITCH_ON
void OperationServer_Handle(const std::shared_ptr<rmw_request_id_t> request_header,
         const std::shared_ptr<example_interfaces::srv::AddTwoInts::Request> request,
         const std::shared_ptr<example_interfaces::srv::AddTwoInts::Response> response);
#else
void OperationServer_Handle(const std::shared_ptr<rmw_request_id_t> request_header,
         const std::shared_ptr<interfaces_tutorial::srv::AddThreeInts::Request> request,
         const std::shared_ptr<interfaces_tutorial::srv::AddThreeInts::Response> response);
#endif
#endif