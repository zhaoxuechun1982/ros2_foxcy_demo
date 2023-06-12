#ifndef POLYGON_PLUGINS__POLYGON_PLUGINS_HPP_
#define POLYGON_PLUGINS__POLYGON_PLUGINS_HPP_

#include <polygon_base/RegularPolygon.hpp>
#include <pluginlib/class_list_macros.hpp>
#include "./visibility_control.h"

namespace polygon_plugins
{
  class Square : public polygon_base::RegularPolygon
  {
    public:
      void initialize(double side_length) override;
      double area() override;
    protected:
      double side_length_;
  };

  class Triangle : public polygon_base::RegularPolygon
  {
    public:
      void initialize(double side_length) override;
      double area() override;
      double getHeight();

    protected:
      double side_length_;
  };
}

PLUGINLIB_EXPORT_CLASS(polygon_plugins::Square, polygon_base::RegularPolygon)
PLUGINLIB_EXPORT_CLASS(polygon_plugins::Triangle, polygon_base::RegularPolygon)

#endif
