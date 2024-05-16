#ifndef DETAIL_HPP
#define DETAIL_HPP
#include <functional>
#include <numeric>
#include <cmath>
#include "shape.hpp"

namespace zaitsev
{
  namespace plh = std::placeholders;
  double get_area(const Polygon& poly);
  double cond_area_sum(double area, const Polygon& poly, std::function< bool(const Polygon&) > cond);
  bool is_odd_size(const Polygon& poly);
  bool is_even_size(const Polygon& poly);
  bool is_equal_size(const Polygon& poly, size_t target);
  bool size_cmp(const Polygon& p1, const Polygon& p2);
  bool area_cmp(const Polygon& p1, const Polygon& p2);
  Point l_bound(Point bound, Point pt);
  Point r_bound(Point bound, Point pt);
  Point left_corner(Point lower, const Polygon& poly);
  Point right_corner(Point upper, const Polygon& poly);
  bool out_of_bounds(Point left_lower, Point right_upper, Point pt);
}
#endif
