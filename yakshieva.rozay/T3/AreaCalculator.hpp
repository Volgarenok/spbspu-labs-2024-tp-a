#ifndef AREA_CALCULATOR_HPP
#define AREA_CALCULATOR_HPP

#include "Polygon.hpp"

namespace yakshieva
{
  double accamulateAllParts(const Polygon& p);
  template < class UnaryPredicate > double calcAreaByCondition(const std::vector< Polygon >& context, UnaryPredicate P);
  double calculateAreaEven(const std::vector< Polygon >& context);
  double calculateAreaOdd(const std::vector< Polygon >& context);
  double calculateAreaMean(const std::vector< Polygon >& context);
  double sumAreaWithNumOfVertices(const std::vector< Polygon >& context, size_t numOfVertices);
  bool minArea(const Polygon& p1, const Polygon& p2);
  bool minVertexes(const Polygon& p1, const Polygon& p2);
  double getMaxArea(const std::vector< Polygon >& polygons);
  size_t getMaxVertexes(const std::vector< Polygon >& polygons);
  double getMinArea(const std::vector< Polygon >& polygons);
  size_t getMinVertexes(const std::vector< Polygon >& polygons);
}

#endif

