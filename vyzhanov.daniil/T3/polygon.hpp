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

  using points = std::vector< Point >::const_iterator;
  double getArea(const Polygon&);
  double calculateArea(points, points, points, points, double);
  double calculatePair(const Point&, const Point&);
  std::istream& operator>>(std::istream&, Polygon&);
  std::ostream& operator<<(std::ostream&, const Polygon&);
  bool operator==(const Polygon&, const Polygon&);
}

#endif
