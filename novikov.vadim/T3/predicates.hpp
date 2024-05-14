#ifndef PREDICATES_HPP
#define PREDICATES_HPP

#include "polygon.hpp"

namespace novikov
{
  bool hasEvenVertexesCount(const Polygon& rhs);
  bool hasOddVertexesCount(const Polygon& rhs);
  bool hasVertexesCount(const Polygon& rhs, std::size_t num);
  bool compareAreas(const Polygon& lhs, const Polygon& rhs);
  bool compareVertexes(const Polygon& lhs, const Polygon& rhs);
  bool comparePointsX(const Point& lhs, const Point& rhs);
  bool comparePointsY(const Point& lhs, const Point& rhs);
  bool comparePolygonsMinX(const Polygon& lhs, const Polygon& rhs);
  bool comparePolygonsMinY(const Polygon& lhs, const Polygon& rhs);
  bool comparePolygonsMaxX(const Polygon& lhs, const Polygon& rhs);
  bool comparePolygonsMaxY(const Polygon& lhs, const Polygon& rhs);
}

#endif
