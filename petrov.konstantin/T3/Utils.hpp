#ifndef UTILS_HPP
#define UTILS_HPP

#include "Geometry.hpp"

namespace petrov
{
  struct AccPolygon
  {
    Point p1;
    double operator()(double area, const Point& p2, const Point& p3);
  };
}

#endif 