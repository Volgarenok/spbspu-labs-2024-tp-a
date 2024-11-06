#ifndef POLYGON_HPP
#define POLYGON_HPP

#include "delimeter.hpp"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <string>
#include <vector>

namespace feofanova
{
  struct Point
  {
    int x, y;
  };
  std::istream& operator>>(std::istream& in, Point& p);
  std::ostream& operator<<(std::ostream& out, const Point& p);
  bool operator==(const Point& point1, const Point& point2);

  struct Polygon
  {
    std::vector< Point > points;
  };
  std::istream& operator>>(std::istream& in, Polygon& p);
  std::ostream& operator<<(std::ostream& out, const Polygon& p);
}

#endif
