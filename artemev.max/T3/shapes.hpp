#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <vector>
#include <iostream>

namespace artemev
{
  struct Point
  {
    int x, y;
  };
  bool operator==(const Point& lhs, const Point& rhs);
  std::istream& operator>>(std::istream& in, Point& point);

  struct Polygon
  {
    std::vector< Point > points;
  };
  double getArea(const Polygon& polygon);
  size_t countRightAngle(const Polygon& polygon);
  std::istream& operator>>(std::istream& in, Polygon& polygon);
}

#endif
