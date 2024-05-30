#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <iostream>
#include <vector>

namespace kravchenko
{
  struct Point
  {
    int x;
    int y;
  };
  bool operator==(const Point& lhs, const Point& rhs);
  std::istream& operator>>(std::istream& in, Point& p);

  struct Polygon
  {
    std::vector< Point > points;
  };
  size_t getNumberOfVertexes(const Polygon& p);
  double getArea(const Polygon& p);
  bool isIdentical(const Polygon& p1, const Polygon& p2);
  bool hasRightAngle(const Polygon& p);
  std::istream& operator>>(std::istream& in, Polygon& p);
}

#endif
