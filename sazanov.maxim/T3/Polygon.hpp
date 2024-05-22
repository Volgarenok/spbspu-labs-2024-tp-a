#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include "Point.hpp"

namespace sazanov
{
  struct Polygon
  {
    std::vector< Point > points;
  };
  bool operator==(const Polygon& lhs, const Polygon& rhs);
  bool operator!=(const Polygon& lhs, const Polygon& rhs);
  double getArea(const Polygon& polygon);
  std::istream& operator>>(std::istream& in, Polygon& polygon);

  struct GetAreaPart
  {
    Point p1;
    double operator()(const Point& p2, const Point& p3);
  };
}

#endif
