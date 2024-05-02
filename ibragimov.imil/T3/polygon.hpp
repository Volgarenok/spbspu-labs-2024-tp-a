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
  int getX(const Point&);
  int getY(const Point&);
  size_t getSize(const Polygon&);
  double getArea(const Polygon&);
}

#endif
