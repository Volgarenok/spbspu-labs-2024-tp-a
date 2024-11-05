#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <iostream>
#include <vector>

namespace skopchenko
{
  struct Point
  {
    int x;
    int y;
  };
  bool operator==(const Point& first, const Point& second);
  bool operator<(const Point& first, const Point& second);
  bool operator<=(const Point& first, const Point& second);
  bool operator>=(const Point& first, const Point& second);
  struct Polygon
  {
    std::vector< Point > points;
  };
}

#endif
