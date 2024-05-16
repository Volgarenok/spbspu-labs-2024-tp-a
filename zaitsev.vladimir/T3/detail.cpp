#include "detail.hpp"
#include <list>
#include <algorithm>
#include <numeric>

int skew_product(std::pair< zaitsev::Point, zaitsev::Point > vects)
{
  return vects.first.x * vects.second.y - vects.first.y * vects.second.x;
}

class KOCTbIJIb
{
public:
  KOCTbIJIb(const zaitsev::Polygon& base):
    points(base.points),
    pos(0)
  {}
  std::pair< zaitsev::Point, zaitsev::Point > operator()()
  {
    pos %= points.size();
    return { points[pos], points[(++pos) % points.size()] };
  }
private:
  const std::vector< zaitsev::Point >& points;
  int pos;
};

double zaitsev::get_area(const Polygon& poly)
{
  using namespace std::placeholders;
  std::list< std::pair< Point, Point > > edges;
  KOCTbIJIb gen(poly);
  std::generate_n(std::back_inserter(edges), poly.points.size(), gen);
  std::list< int > sizes;
  std::transform(edges.begin(), edges.end(), std::back_inserter(sizes), skew_product);
  return std::fabs(std::accumulate(sizes.begin(), sizes.end(), 0) / 2.0);
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
