#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <iostream>
#include <vector>
#include "point.hpp"

namespace lebedev
{
  struct Polygon
  {
    std::vector< Point > points;
  };
  std::istream & operator>>(std::istream & input, Polygon & polygon);
  double getArea(const Polygon & polygon);
}

#endif
