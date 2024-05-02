#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <vector>
#include <iostream>

namespace artemev
{
  struct Point
  {
    int x, y;
    bool operator==(const Point& oth) const;
  };
  std::istream& operator>>(std::istream& in, Point& point);

  struct Polygon
  {
    std::vector< Point > points;
    bool operator==(const Polygon& oth) const;
    double getArea() const;
  };
  std::istream& operator>>(std::istream& in, Polygon& polygon);
}

#endif