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
  std::istream& operator>>(std::istream& in, Polygon& rhs);
  bool operator==(const Polygon& lhs, const Polygon& rhs);
  double getArea(const Polygon& rhs);
}

#endif
