#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <istream>
#include <vector>
#include "point.hpp"

namespace ibragimov
{
  struct Polygon
  {
    std::vector< Point > points;
  };
  std::istream& operator>>(std::istream&, Polygon&);
  size_t getSize(const Polygon&);
  double getArea(const Polygon&);
}

#endif
