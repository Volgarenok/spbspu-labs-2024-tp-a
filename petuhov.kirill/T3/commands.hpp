#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "polygon.hpp"
#include <vector>

namespace petuhov
{
  int same_count(const std::vector<Polygon>& polygons, const Polygon& target);
  int perms_count(const std::vector<Polygon>& polygons, const Polygon& target);
  int right_shapes_count(const std::vector<Polygon>& polygons);
  std::vector<Point> normalize(const Polygon &polygon);
  bool is_permutation(const Polygon &a, const Polygon &b);
}

#endif
