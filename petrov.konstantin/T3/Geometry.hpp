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

  struct Polygon
  {
    std::vector< Point > points;
  };
  std::istream& operator>>(std::istream& in, Polygon& dest);
  std::ostream& operator<<(std::ostream& in, const Polygon& src);

  double getArea(const Polygon& src);
}

#endif
