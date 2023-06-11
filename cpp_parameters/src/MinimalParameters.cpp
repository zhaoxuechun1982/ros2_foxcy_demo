#include <chrono>
#include <functional>
#include <string>
#include "../include/cpp_parameters/MinimalParameters.hpp"

MinimalParameters::MinimalParameters(): Node("minimal_parameters_node")
{
  //this->declare_parameter("my_parameters", "world");
  auto param_desc = rcl_interfaces::msg::ParameterDescriptor{};
  param_desc.description = "This parameter is mine!";  
  this->declare_parameter("my_parameters", "world", param_desc);

  timer_ = this->create_wall_timer(1000ms, std::bind(&MinimalParameters::TimerCallback, this));
}

void MinimalParameters::TimerCallback()
{
  std::string my_param = this->get_parameter("my_parameters").as_string();  
  RCLCPP_INFO(this->get_logger(), "Hello %s!", my_param.c_str());  
//   std::vector<rclcpp::Parameter> all_new_parameters{rclcpp::Parameter("my_parameters", "world")};
//   this->set_parameters(all_new_parameters);
}