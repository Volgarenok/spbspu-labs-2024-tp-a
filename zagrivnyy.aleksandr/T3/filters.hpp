#ifndef FILTERS_HPP
#define FILTERS_HPP
#include <functional>

#include "polygon.hpp"

namespace zagrivnyy
{
  bool isOdd(const Polygon &p);
  bool isEven(const Polygon &p);
  bool isIntersects(const Polygon &p1, const Polygon &p2);
  bool isVertexesCount(size_t count, const Polygon &p);
  bool compareAreas(const Polygon &p1, const Polygon &p2);
  bool compareVertexes(const Polygon &p1, const Polygon &p2);

  double calcMeanArea(const Polygon &p, size_t polygons);
}

#endif
