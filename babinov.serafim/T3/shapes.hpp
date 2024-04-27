#ifndef SHAPES_HPP
#define SHAPES_HPP
#include <istream>
#include <vector>

namespace babinov
{
  struct Point
  {
    int x, y;
  };
  std::istream& operator>>(std::istream& in, Point& point);

  struct Polygon
  {
    std::vector< Point > points;
  };
  std::istream& operator>>(std::istream& in, Polygon& polygon);

  double getArea(const Polygon& polygon);
}

#endif
