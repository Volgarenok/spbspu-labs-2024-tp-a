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
  int doubled_sum = origin_area(poly.points[poly.points.size() - 1], poly.points[0]);
  for (auto i = poly.points.begin(); i != --poly.points.end(); ++i)
  {
    doubled_sum += origin_area(*i, *(std::next(i)));
  }
  return std::fabs(doubled_sum / 2.0);
}
double zaitsev::cond_area_sum(double area, const Polygon& poly, std::function< bool(const Polygon&) > cond)
{
  return area + (cond(poly) ? get_area(poly) : 0.0);
}
bool zaitsev::is_odd_size(const Polygon& poly)
{
  return poly.points.size() % 2 == 1;
}
bool zaitsev::is_even_size(const Polygon& poly)
{
  return poly.points.size() % 2 == 0;
}
bool zaitsev::is_equal_size(const Polygon& poly, size_t target)
{
  return poly.points.size() == target;
}
bool zaitsev::size_cmp(const Polygon& p1, const Polygon& p2)
{
  return p1.points.size() < p2.points.size();
}
bool zaitsev::area_cmp(const Polygon& p1, const Polygon& p2)
{
  return  get_area(p1) < get_area(p2);
}
zaitsev::Point zaitsev::l_bound(Point bound, Point pt)
{
  return Point{ std::min(bound.x, pt.x), std::min(bound.y, pt.y) };
}
zaitsev::Point zaitsev::r_bound(Point bound, Point pt)
{
  return Point{ std::max(bound.x, pt.x), std::max(bound.y, pt.y) };
}
zaitsev::Point zaitsev::left_corner(Point lower, const Polygon& poly)
{
  return l_bound(lower, std::accumulate(poly.points.begin(), poly.points.end(), poly.points[0], l_bound));
}
zaitsev::Point zaitsev::right_corner(Point upper, const Polygon& poly)
{
  return r_bound(upper, std::accumulate(poly.points.begin(), poly.points.end(), poly.points[0], r_bound));
}
bool zaitsev::out_of_bounds(Point left_lower, Point right_upper, Point pt)
{
  return (pt.x > right_upper.x || pt.x < left_lower.x || pt.y > right_upper.y || pt.y < left_lower.y);
}
