#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <istream>
#include <vector>

namespace stepanchenko
{
  struct Point
  {
    int x, y;
  };

  struct Polygon
  {
    std::vector< Point > points;
  };

  std::istream& operator>>(std::istream& in, Point& point);
  std::istream& operator>>(std::istream& in, Polygon& polygon);
  bool operator==(const Point& right, const Point& left);
  bool operator<=(const Point& right, const Point& left);
  bool operator==(const Polygon& right, const Polygon& left);
}

#endif
