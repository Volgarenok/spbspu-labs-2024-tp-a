#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <vector>
#include <iostream>

namespace petrov
{
  struct Point
  {
    int x, y;
  };
  std::istream& operator>>(std::istream& in, Point& dest);
  std::ostream& operator<<(std::ostream& out, const Point& src);
  bool operator==(const Point& p1, const Point& p2);
  Point getDelta(const Point& p1, const Point& p2);

  struct Polygon
  {
    std::vector< Point > points;
  };
  std::istream& operator>>(std::istream& in, Polygon& dest);
  std::ostream& operator<<(std::ostream& in, const Polygon& src);
  bool operator==(const Polygon& p1, const Polygon& p2);

  double getArea(const Polygon& src);
}

#endif
