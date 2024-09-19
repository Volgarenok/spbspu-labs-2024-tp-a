#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <istream>

namespace gladyshev
{
  struct Point
  {
    int x, y;
  };
  std::istream& operator>>(std::istream& in, Point& pnt);
  struct Polygon
  {
    std::vector< Point > points;
  };
  double findArea(const Polygon& poly);
  bool operator==(const Polygon& left, const Polygon& right);
  bool operator==(const Point& left, const Point& right);
  std::istream& operator>>(std::istream& in, Polygon& poly);
}

#endif
