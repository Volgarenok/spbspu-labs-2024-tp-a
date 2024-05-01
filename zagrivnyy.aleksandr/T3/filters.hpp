#ifndef FILTERS_HPP
#define FILTERS_HPP
#include <functional>

#include "polygon.hpp"

namespace zagrivnyy
{
  enum Parity
  {
    EVEN = 0,
    ODD = 1
  };

  bool checkParity(const Polygon &p, const Parity &parity);
  double addAreaIf(double area, const Polygon &p, bool condition);
  bool isIntersects(const Polygon &p1, const Polygon &p2);
}

#endif
