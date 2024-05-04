#include "detail.hpp"

int skew_product(zaitsev::Point v1, zaitsev::Point v2)
{
  return v1.x * v2.y - v1.y * v2.x;
}
int doubled_area(zaitsev::Point v1, zaitsev::Point v2, zaitsev::Point v3)
{
  return skew_product(v2 - v1, v3 - v1);
}
double zaitsev::get_area(const Polygon& poly)
{
  using namespace std::placeholders;
  auto origin_area = std::bind(doubled_area, Point{ 0, 0 }, plh::_1, plh::_2);
  int doubled_sum = origin_area(poly.points[0], poly.points[poly.points.size() - 1]);
  for (auto i = poly.points.begin(); i != --poly.points.end(); ++i)
  {
    doubled_sum += origin_area(*i, *(std::next(i)));
  }
  return std::fabs(doubled_sum / 2.0);
}
size_t zaitsev::cond_count(size_t counter, const Polygon& poly, std::function< bool(const Polygon&) > cond)
{
  return counter + cond(poly);
}
double zaitsev::cond_area_sum(double area, const Polygon& poly, std::function< bool(const Polygon&) > cond)
{
  return area + (cond(poly) ? get_area(poly) : 0.0);
}
size_t zaitsev::extremum_size(size_t extrem, const Polygon& poly, std::function< size_t(size_t, size_t) > cond)
{
  return cond(extrem, poly.points.size());
}
double zaitsev::extremum_area(double extrem, const Polygon& poly, std::function< double(double, double) > cond)
{
  return cond(extrem, get_area(poly));
}
bool zaitsev::is_odd_size(const Polygon& poly)
{
  return poly.points.size() % 2 == 0;
}
bool zaitsev::is_even_size(const Polygon& poly)
{
  return poly.points.size() % 2 == 1;
}
bool zaitsev::is_equal_size(const Polygon& poly, size_t target)
{
  return poly.points.size() == target;
}
bool zaitsev::less_area(const Polygon& poly, double target_area)
{
  return get_area(poly) < target_area;
}
zaitsev::Point zaitsev::l_bound(Point bound, Point pt)
{
  return Point{ min(bound.x, pt.x), min(bound.y, pt.y) };
}
zaitsev::Point zaitsev::r_bount(Point bound, Point pt)
{
  return Point{ max(bound.x, pt.x), max(bound.y, pt.y) };
}
zaitsev::Point zaitsev::left_corner(Point lower, const Polygon& poly)
{
  return l_bound(lower, std::accumulate(poly.points.begin(), poly.points.end(), poly.points[0], l_bound));
}
zaitsev::Point zaitsev::right_corner(Point upper, const Polygon& poly)
{
  return r_bount(upper, std::accumulate(poly.points.begin(), poly.points.end(), poly.points[0], l_bound));
}
size_t zaitsev::out_of_bounds(size_t outs_nmb, Point left_lower, Point right_upper, Point pt)
{
  return outs_nmb + (pt.x > right_upper.x || pt.x < left_lower.x || pt.y > right_upper.y || pt.y < left_lower.y);
}
