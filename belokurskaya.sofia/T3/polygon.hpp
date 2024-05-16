#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>

#include "point.hpp"

namespace belokurskaya
{
  struct Polygon
  {
    std::vector< Point > points;
  };

  struct RectVector
  {
    Point vertexes;
    RectVector(const Point& p1, const Point& p2);
    double operator*(const RectVector& p1);
    double getLength() const;
    double cos(const RectVector& p1);
  };

  std::istream& operator>>(std::istream& in, Polygon& polygon);
  bool operator==(const Polygon& lhs, const Polygon& rhs);
}

#endif
