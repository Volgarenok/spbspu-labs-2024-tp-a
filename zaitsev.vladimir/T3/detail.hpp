#ifndef DETAIL_HPP
#define DETAIL_HPP
#include <algorithm>
#include <functional>
#include <numeric>
#include <cmath>
#include <list>
#include "shape.hpp"

namespace zaitsev
{
  namespace plh = std::placeholders;
  double get_area(const Polygon& poly);
  size_t cond_count(size_t counter, const Polygon& poly, std::function< bool(const Polygon&) > cond);
  double cond_area_sum(double area, const Polygon& poly, std::function< bool(const Polygon&) > cond);
  size_t extremum_size(size_t extrem, const Polygon& poly, std::function< size_t(size_t, size_t) > cond);
  double extremum_area(double extrem, const Polygon& poly, std::function< double(double, double) > cond);
  bool is_odd_size(const Polygon& poly);
  bool is_even_size(const Polygon& poly);
  bool is_equal_size(const Polygon& poly, size_t target);
  bool less_area(const Polygon& poly, double target_area);
  template< class T >
  T max(T a, T b)
  {
    return a > b ? a : b;
  }
  template< class T >
  T min(T a, T b)
  {
    return a < b ? a : b;
  }
  Point l_bound(Point bound, Point pt);
  Point r_bount(Point bound, Point pt);
  Point left_corner(Point lower, const Polygon& poly);
  Point right_corner(Point upper, const Polygon& poly);
  size_t out_of_bounds(size_t outs_nmb, Point left_lower, Point right_upper, Point pt);
}
#endif
