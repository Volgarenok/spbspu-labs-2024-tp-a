#ifndef SHAPE_HPP
#define SHAPE_HPP
#include <vector>
#include <iostream>
#include <limits>
#include <algorithm>
#include <iterator>
#include <delimiter.hpp>

namespace zaitsev
{
  struct Point
  {
    int x, y;
  };
  struct Polygon
  {
    std::vector< Point > points;
  };
  std::istream& operator>>(std::istream& in, Point& val);
  std::istream& operator>>(std::istream& in, Polygon& val);
  Point operator+(Point pt1, Point pt2);
  Point operator-(Point pt1, Point pt2);
}
#endif
