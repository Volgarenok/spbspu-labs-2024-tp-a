#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include "point.hpp"

namespace novikov
{
  struct Polygon
  {
    std::vector< Point > points;
  };
  std::istream& operator>>(std::istream& in, Polygon& polygon);
  bool operator==(const Polygon& lhs, const Polygon& polygon);
  int getDeterminantByPoint(const Polygon& polygon, const Point& point);
  double getArea(const Polygon& polygon);
}

#endif
