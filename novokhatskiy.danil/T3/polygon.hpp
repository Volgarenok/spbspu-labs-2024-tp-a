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
  std::istream& operator>>(std::istream& in, Point& p);
  std::ostream& operator<<(std::ostream& out, const Point& p);

  struct Polygon
  {
    std::vector< Point > points;
  };
  std::istream& operator>>(std::istream& in, Polygon& p);
  std::ostream& operator<<(std::ostream& out, const Polygon& p);
}

#endif
