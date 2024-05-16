#ifndef DETAIL_HPP
#define DETAIL_HPP
#include <list>
#include <functional>
#include "shape.hpp"

namespace zaitsev
{
  namespace plh = std::placeholders;
  double get_area(const Polygon& poly);
  double cond_area_sum(const std::list< Polygon >& polys, std::function< bool(const Polygon&) > cond);
  bool is_odd_size(const Polygon& poly);
  bool is_even_size(const Polygon& poly);
  bool is_equal_size(const Polygon& poly, size_t target);
  bool true_function(const Polygon& poly);
  bool size_cmp(const Polygon& p1, const Polygon& p2);
  bool area_cmp(const Polygon& p1, const Polygon& p2);
  bool out_of_bounds(std::pair<Point, Point> bounds, Point pt);
  std::pair< zaitsev::Point, zaitsev::Point > frame_rect(const std::vector< Point >& pts);
  std::pair< Point, Point > big_frame_rect(const std::list< Polygon >& poly);
}
#endif
