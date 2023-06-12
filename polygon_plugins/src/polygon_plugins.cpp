#include <cmath>
#include "../include/polygon_plugins/polygon_plugins.hpp"

namespace polygon_plugins
{
  void Square::initialize(double side_length)
  {
    side_length_ = side_length;
  }
  
  double Square::area()
  {
    return side_length_ * side_length_;
  }

  void Triangle::initialize(double side_length)
  {
    side_length_ = side_length;
  }
  double Triangle::area()
  {
    return 0.5 * side_length_ * getHeight();
  }
  double Triangle::getHeight()
  {
    return sqrt((side_length_ * side_length_) - ((side_length_ / 2) * (side_length_ / 2)));
  }
}
