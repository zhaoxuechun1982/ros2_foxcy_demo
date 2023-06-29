#ifndef OPERATION_CLIENT_HPP
#define OPERATION_CLIENT_HPP
#include "rclcpp/rclcpp.hpp"
#include "InterfacesConfig.h"

#ifndef CUSTOM_INTERFACES_SWITCH_ON
#include "example_interfaces/srv/add_two_ints.hpp"
#else
#include "interfaces_tutorial/srv/add_three_ints.hpp" 
#endif

#include <memory>

#ifndef CUSTOM_INTERFACES_SWITCH_ON
void OperationClient_Handle(const std::shared_ptr<rclcpp::Node>& node,
                        const rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedPtr& client,
                        const std::shared_ptr<example_interfaces::srv::AddTwoInts_Request>& request);
#else
void OperationClient_Handle(const std::shared_ptr<rclcpp::Node>& node,
                        const rclcpp::Client<interfaces_tutorial::srv::AddThreeInts>::SharedPtr& client,
                        const std::shared_ptr<interfaces_tutorial::srv::AddThreeInts_Request>& request);
#endif

#endif