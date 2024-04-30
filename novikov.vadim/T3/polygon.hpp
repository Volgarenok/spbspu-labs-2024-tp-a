#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include "point.hpp"

namespace novikov
{
  struct LimitTo
  {
    int n;
    bool operator()();
  };

  struct Polygon
  {
    std::vector< Point > points;
  };
  std::istream& operator>>(std::istream& in, Polygon& rhs);
  std::ostream& operator<<(std::ostream& out, const Polygon& rhs);
  bool operator==(const Polygon& lhs, const Polygon& rhs);
  double getArea(const Polygon& rhs);
  int minX(const Polygon& polygon);
  int minY(const Polygon& polygon);
  int maxX(const Polygon& polygon);
  int maxY(const Polygon& polygon);
}

#endif
