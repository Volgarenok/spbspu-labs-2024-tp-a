#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <istream>
#include <vector>

namespace felk
{
  struct Point
  {
    int x, y;
  };

  struct Polygon
  {
    std::vector< Point > points;
  };
  std::istream& operator>>(std::istream& in, Polygon& data);
  std::istream& operator>>(std::istream& in, Point& data);
  bool operator==(const Point& point1, const Point& point2);
  bool operator==(const Polygon& poly1, const Polygon& poly2);
}

#endif
