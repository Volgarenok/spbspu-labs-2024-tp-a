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

  std::istream& operator>>(std::istream& in, Polygon& polygon);
  std::ostream& operator<<(std::ostream& out, const Polygon& polygon);
}

#endif
