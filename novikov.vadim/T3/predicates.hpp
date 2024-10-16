#ifndef PREDICATES_HPP
#define PREDICATES_HPP

#include "polygon.hpp"

namespace novikov
{
  bool hasEvenVertexesCount(const Polygon& polygon);
  bool hasOddVertexesCount(const Polygon& polygon);
  bool hasVertexesCount(const Polygon& polygon, size_t num);
  bool compareAreas(const Polygon& lhs, const Polygon& rhs);
  bool compareVertexes(const Polygon& lhs, const Polygon& rhs);
  bool comparePointsX(const Point& lhs, const Point& rhs);
  bool comparePointsY(const Point& lhs, const Point& rhs);
  bool comparePolygonsMinX(const Polygon& lhs, const Polygon& rhs);
  bool comparePolygonsMinY(const Polygon& lhs, const Polygon& rhs);
  bool comparePolygonsMaxX(const Polygon& lhs, const Polygon& rhs);
  bool comparePolygonsMaxY(const Polygon& lhs, const Polygon& rhs);
  using minmax_pair_t = std::pair< std::vector< Point >::const_iterator,  std::vector< Point >::const_iterator >;
  bool isLayingIn(const minmax_pair_t& in_x, const minmax_pair_t& in_y, const minmax_pair_t& out_x, const minmax_pair_t& out_y);
}

#endif
