#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <iostream>
#include "point.hpp"

namespace vyzhanov
{
  struct Polygon
  {
    std::vector< Point > points;
  };
  using pnts = std::vector< Point >::const_iterator;
  double calculateArea(pnts, pnts, pnts, pnts, double);
  double calculatePair(const Point&, const Point&);
  double getPolygonArea(const Polygon&);
  std::istream& operator>>(std::istream&, Polygon&);
  std::ostream& operator<<(std::ostream&, const Polygon&);
  bool operator==(const Polygon&, const Polygon&);
}

#endif
