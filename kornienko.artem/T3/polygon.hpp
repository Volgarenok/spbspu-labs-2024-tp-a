#ifndef POLYGON_H
#define POLYGON_H

#include <iostream>
#include <vector>

#include "delimeter.hpp"

namespace kornienko
{
  struct Point
  {
    int x, y;
  };
  struct Polygon
  {
    std::vector< Point > points;
  };

  std::istream & operator>>(std::istream & in, Point & point);
  std::ostream & operator<<(std::ostream & out, const Point & point);
}

#endif
