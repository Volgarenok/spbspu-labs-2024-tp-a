#include "detail.hpp"
#include <list>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <cmath>

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
    pos = (pos + 1) % points.size();
    return { points[pos], points[(pos + 1) % points.size()] };
  }
private:
  const std::vector< zaitsev::Point >& points;
  size_t pos;
};

double zaitsev::get_area(const Polygon& poly)
{
  using namespace std::placeholders;
  std::list< std::pair< Point, Point > > edges;
  KOCTbIJIb gen(poly);
  std::generate_n(std::back_inserter(edges), poly.points.size(), gen);
  std::list< int > areas;
  std::transform(edges.begin(), edges.end(), std::back_inserter(areas), skew_product);
  return std::fabs(std::accumulate(areas.begin(), areas.end(), 0) / 2.0);
}
double zaitsev::cond_area_sum(const std::list< Polygon >& polys, std::function< bool(const Polygon&) > cond)
{
  std::list< Polygon >satisfy_cond;
  std::copy_if(polys.begin(), polys.end(), std::back_inserter(satisfy_cond), cond);
  std::list< double > areas;
  std::transform(satisfy_cond.begin(), satisfy_cond.end(), std::back_inserter(areas), get_area);
  return std::accumulate(areas.begin(), areas.end(), 0.0);
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
bool zaitsev::true_function(const Polygon& poly)
{
  return poly.points == poly.points;
}
bool zaitsev::size_cmp(const Polygon& p1, const Polygon& p2)
{
  return p1.points.size() < p2.points.size();
}
bool zaitsev::area_cmp(const Polygon& p1, const Polygon& p2)
{
  return  get_area(p1) < get_area(p2);
}
std::pair< zaitsev::Point, zaitsev::Point > zaitsev::frame_rect(const std::vector< Point >& pts)
{
  auto cmp_x = [](Point lhs, Point rhs)
    {
      return lhs.x < rhs.x;
    };
  auto cmp_y = [](Point lhs, Point rhs)
    {
      return lhs.y < rhs.y;
    };
  auto bounds_x = std::minmax_element(pts.begin(), pts.end(), cmp_x);
  auto bounds_y = std::minmax_element(pts.begin(), pts.end(), cmp_y);
  return { { bounds_x.first->x, bounds_y.first->y }, { bounds_x.second->x, bounds_y.second->y } };
}

std::pair< zaitsev::Point, zaitsev::Point > zaitsev::big_frame_rect(const std::list< Polygon >& poly)
{
  using rect_bounds = std::pair< zaitsev::Point, zaitsev::Point >;
  auto get_min = [](rect_bounds bounds)
    {
      return bounds.first;
    };
  auto get_max = [](rect_bounds bounds)
    {
      return bounds.second;
    };
  auto wrapper = [](const Polygon& poly)
    {
      return frame_rect(poly.points);
    };
  std::list< rect_bounds > bounds;
  std::vector< Point> bound_points;
  std::transform(poly.begin(), poly.end(), std::back_inserter(bounds), wrapper);
  std::transform(bounds.begin(), bounds.end(), std::back_inserter(bound_points), get_min);
  std::transform(bounds.begin(), bounds.end(), std::back_inserter(bound_points), get_max);
  return frame_rect(bound_points);
}

bool zaitsev::out_of_bounds(std::pair<Point, Point> bounds, Point pt)
{
  return (pt.x < bounds.first.x || pt.x > bounds.second.x || pt.y < bounds.first.y || pt.y > bounds.second.y);
}
