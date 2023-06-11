#include <rclcpp/rclcpp.hpp>

using namespace std::chrono_literals;

class MinimalParameters : public rclcpp::Node
{
public:
  MinimalParameters();
  void TimerCallback();
private:
  rclcpp::TimerBase::SharedPtr timer_;
};