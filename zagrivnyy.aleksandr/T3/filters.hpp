#ifndef FILTERS_HPP
#define FILTERS_HPP
#include <functional>

#include "polygon.hpp"

namespace zagrivnyy
{
  bool isOdd(const Polygon &p);
  bool isEven(const Polygon &p);
  // TODO: Remove its
  double addAreaIf(double area, const Polygon &p, bool condition);
  bool isIntersects(const Polygon &p1, const Polygon &p2);
  bool isVertexesCount(size_t count, const Polygon &p);

  double calcMeanArea(const Polygon &p, size_t polygons);
}

#endif
