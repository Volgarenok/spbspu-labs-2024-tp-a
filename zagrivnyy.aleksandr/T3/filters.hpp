#ifndef FILTERS_HPP
#define FILTERS_HPP
#include <functional>

#include "polygon.hpp"

namespace zagrivnyy
{
  bool isOdd(const Polygon &p);
  bool isEven(const Polygon &p);
  double addAreaIf(double area, const Polygon &p, bool condition);
  bool isIntersects(const Polygon &p1, const Polygon &p2);
}

#endif
