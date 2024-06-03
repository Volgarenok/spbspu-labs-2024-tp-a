#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <iostream>
#include <vector>

namespace novokhatskiy
{
  struct Point
  {
    int x, y;
  };
  bool operator==(const Point& lhs, const Point& rhs);
  std::istream& operator>>(std::istream& in, Point& p);
  std::ostream& operator<<(std::ostream& out, const Point& p);

  struct Polygon
  {
    std::vector< Point > points;
  };

  double getArea(const Polygon& points);

  std::istream& operator>>(std::istream& in, Polygon& p);
  bool operator<(const Point& lhs, const Point& rhs);
  bool operator<(const Polygon& lhs, const Polygon& rhs);
}

#endif
