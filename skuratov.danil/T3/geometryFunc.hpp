#ifndef GEOMETRY_FUNC_HPP
#define GEOMETRY_FUNC_HPP

#include "polygon.hpp"

namespace skuratov
{
  bool isEven(const Polygon& polygon);
  bool isOdd(const Polygon& polygon);
  double calculateSumOfAreas(double sum, const Polygon& polygon, std::function< bool(const Polygon& polygon)> state);
  double isMean(double averageArea, const Polygon& polygon, size_t numOfPolygons);
  double isNumOfVertexes(double sumOfAreas, const Polygon& polygon, size_t numOfVertexes);
}

#endif
