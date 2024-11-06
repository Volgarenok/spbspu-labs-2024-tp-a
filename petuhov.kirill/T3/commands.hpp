#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include "polygon.hpp"

namespace petuhov {

  int same_count(const std::vector<Polygon>& polygons, const Polygon& target);
  int perms_count(const std::vector<Polygon>& polygons, const Polygon& target);

  bool has_right_angle(const Polygon& poly);
  int right_shapes_count(const std::vector<Polygon>& polygons);

  std::vector<Point> normalize(const Polygon& polygon);
  bool is_permutation(const Polygon& a, const Polygon& b);

  double calculate_area(const Polygon& poly);
  double sum_area(const std::vector<Polygon>& polygons, bool even);
  double mean_area(const std::vector<Polygon>& polygons);
  double sum_area_by_vertex_count(const std::vector<Polygon>& polygons, int vertex_count);

  int max_vertex_count(const std::vector<Polygon>& polygons);
  double max_area(const std::vector<Polygon>& polygons);

  int min_vertex_count(const std::vector<Polygon>& polygons);
  double min_area(const std::vector<Polygon>& polygons);

  int count_by_vertex_parity(const std::vector<Polygon>& polygons, bool even);
  int count_by_vertex_count(const std::vector<Polygon>& polygons, int vertex_count);

}

#endif
