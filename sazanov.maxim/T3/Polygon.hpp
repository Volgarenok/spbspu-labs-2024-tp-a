#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include "Point.hpp"

namespace sazanov
{
  struct Polygon
  {
    std::vector< Point > points;
    double getArea();
  };
  std::istream& operator>>(std::istream& in, Polygon& polygon);
  std::ostream& operator<<(std::ostream& out, const Polygon& polygon);
}

#endif
