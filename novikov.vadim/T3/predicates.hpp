#ifndef PREDICATES_HPP
#define PREDICATES_HPP

#include "polygon.hpp"

namespace novikov
{
  bool even_vertexes(const Polygon& rhs);
  bool odd_vertexes(const Polygon& rhs);
  bool vertexes_count(const Polygon& rhs, std::size_t num);
  bool compare_areas(const Polygon& lhs, const Polygon& rhs);
  bool compare_vertexes(const Polygon& lhs, const Polygon& rhs);
  bool compare_points_x(const Point& lhs, const Point& rhs);
  bool compare_points_y(const Point& lhs, const Point& rhs);
  bool compare_polygons_x(const Polygon& lhs, const Polygon& rhs);
  bool compare_polygons_y(const Polygon& lhs, const Polygon& rhs);
}

#endif
