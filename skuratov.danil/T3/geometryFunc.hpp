#ifndef GEOMETRY_FUNC_HPP
#define GEOMETRY_FUNC_HPP

#include "polygon.hpp"

namespace skuratov
{
  bool isEven(const Polygon& polygon);
  bool isOdd(const Polygon& polygon);
  double isMean(const Polygon& polygon, size_t numOfPolygons, double area);
  double isNumOfVertexes(const Polygon& polygon, size_t numOfVertexes, double sumOfAreas);
}

#endif
