#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <iostream>
#include <vector>

namespace lebedev
{
  struct Point
  {
    int x, y;
  };
  std::istream & operator>>(std::istream & input, Point & point);

  struct Polygon
  {
    std::vector< Point > points;
  };
}

#endif
