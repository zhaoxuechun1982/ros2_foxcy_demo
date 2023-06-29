#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "InterfacesConfig.h"

#ifndef CUSTOM_INTERFACES_SWITCH_ON
#include "std_msgs/msg/string.hpp"
#else
#include "interfaces_tutorial/msg/num.hpp"
#endif

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
* member function as a callback from the timer. */

class MinimalPublisher : public rclcpp::Node
{
public:
  MinimalPublisher();

private:
  void TimerCallback(void);  
  rclcpp::TimerBase::SharedPtr timer_;

#ifndef CUSTOM_INTERFACES_SWITCH_ON
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
#else
  rclcpp::Publisher<interfaces_tutorial::msg::Num>::SharedPtr publisher_;
#endif

  size_t count_;
};