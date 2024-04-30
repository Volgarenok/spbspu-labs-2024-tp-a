#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <istream>
#include <vector>
#include "point.hpp"

namespace novikov
{
  struct Polygon
  {
    std::vector< Point > points;
  };
  std::istream& operator>>(std::istream& in, Polygon& rhs);
  std::ostream& operator<<(std::ostream& out, const Polygon& rhs);
  bool operator==(const Polygon& lhs, const Polygon& rhs);
  double get_area(const Polygon& rhs);
  int min_x(const Polygon& polygon);
  int min_y(const Polygon& polygon);
  int max_x(const Polygon& polygon);
  int max_y(const Polygon& polygon);
}

#endif
