#include "commands.hpp"
#include <iterator>
#include <algorithm>
#include <functional>
#include <string>
#include <iomanip>
#include <numeric>
#include <cmath>
#include <stream_guard.hpp>

namespace plh = std::placeholders;

class generator
{
public:
  generator(const zaitsev::Polygon& base);
  std::pair< zaitsev::Point, zaitsev::Point > operator()();
private:
  const std::vector< zaitsev::Point >& points;
  size_t pos;
};
int skew_product(std::pair< zaitsev::Point, zaitsev::Point > vects);
double get_area(const zaitsev::Polygon& poly);
double cond_area_sum(const std::list< zaitsev::Polygon >& polys, std::function< bool(const zaitsev::Polygon&) > cond);
bool is_odd_size(const zaitsev::Polygon& poly);
bool is_even_size(const zaitsev::Polygon& poly);
bool is_equal_size(const zaitsev::Polygon& poly, size_t target);
bool true_function(const zaitsev::Polygon& poly);
bool size_cmp(const zaitsev::Polygon& p1, const zaitsev::Polygon& p2);
bool area_cmp(const zaitsev::Polygon& p1, const zaitsev::Polygon& p2);
std::pair< zaitsev::Point, zaitsev::Point > frame_rect(const std::vector< zaitsev::Point >& pts);
std::pair< zaitsev::Point, zaitsev::Point > big_frame_rect(const std::list< zaitsev::Polygon >& poly);
bool out_of_bounds(std::pair< zaitsev::Point, zaitsev::Point > bounds, zaitsev::Point pt);

std::ostream& zaitsev::area_cmd(std::istream& in, std::ostream& out, std::list< Polygon >& shapes)
{
  StreamGuard guard(out);
  out << std::fixed << std::setprecision(1);
  std::string arg;
  in >> arg;
  in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  if (arg == "EVEN")
  {
    return out << cond_area_sum(shapes, is_even_size) << '\n';
  }
  if (arg == "ODD")
  {
    return out << cond_area_sum(shapes, is_odd_size) << '\n';
  }
  if (!shapes.empty() && arg == "MEAN")
  {
    return out << cond_area_sum(shapes, true_function) / shapes.size() << '\n';
  }
  size_t sz = std::stoull(arg);
  if (sz < 3)
  {
    throw std::invalid_argument("");
  }
  std::function< bool(const Polygon&) > cond = std::bind(is_equal_size, plh::_1, sz);
  return out << cond_area_sum(shapes, cond) << '\n';
}

std::ostream& zaitsev::max_cmd(std::istream& in, std::ostream& out, std::list< Polygon >& shapes)
{
  std::string arg;
  in >> arg;
  in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  if (!shapes.empty() && arg == "AREA")
  {
    StreamGuard guard(out);
    out << std::fixed << std::setprecision(1);
    return out << get_area(*(std::max_element(shapes.begin(), shapes.end(), area_cmp))) << '\n';
  }
  if (!shapes.empty() && arg == "VERTEXES")
  {
    return out << std::max_element(shapes.begin(), shapes.end(), size_cmp)->points.size() << '\n';
  }
  throw std::invalid_argument("");
}

std::ostream& zaitsev::min_cmd(std::istream& in, std::ostream& out, std::list< Polygon >& shapes)
{
  std::string arg;
  in >> arg;
  in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  if (!shapes.empty() && arg == "AREA")
  {
    StreamGuard guard(out);
    out << std::fixed << std::setprecision(1);
    return out << get_area(*(std::min_element(shapes.begin(), shapes.end(), area_cmp))) << '\n';
  }
  if (!shapes.empty() && arg == "VERTEXES")
  {
    return out << std::min_element(shapes.begin(), shapes.end(), size_cmp)->points.size() << '\n';
  }
  throw std::invalid_argument("");
}

std::ostream& zaitsev::count_cmd(std::istream& in, std::ostream& out, std::list< Polygon>& shapes)
{
  std::string arg;
  in >> arg;
  in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  if (arg == "EVEN")
  {
    return out << std::count_if(shapes.begin(), shapes.end(), is_even_size) << '\n';
  }
  if (arg == "ODD")
  {
    return out << std::count_if(shapes.begin(), shapes.end(), is_odd_size) << '\n';
  }
  size_t sz = std::stoull(arg);
  if (sz < 3)
  {
    throw std::invalid_argument("");
  }
  std::function< bool(const Polygon&) > cond = std::bind(is_equal_size, plh::_1, sz);
  return out << std::count_if(shapes.begin(), shapes.end(), cond) << '\n';
}

std::ostream& zaitsev::lessarea_cmd(std::istream& in, std::ostream& out, std::list< Polygon>& shapes)
{
  Polygon target;
  in >> target;
  if (!in)
  {
    throw std::invalid_argument("");
  }
  std::function< bool(const Polygon&) > cond = std::bind(area_cmp, plh::_1, target);
  return out << std::count_if(shapes.begin(), shapes.end(), cond) << '\n';
}

std::ostream& zaitsev::inframe_cmd(std::istream& in, std::ostream& out, std::list< Polygon>& shapes)
{
  Polygon p;
  in >> p;
  if (!in)
  {
    throw std::invalid_argument("");
  }
  std::pair< Point, Point> bounds = big_frame_rect(shapes);
  std::function< bool(Point) > cond = std::bind(out_of_bounds, bounds, plh::_1);
  return out << (std::find_if(p.points.begin(), p.points.end(), cond) == p.points.end() ? "<TRUE>\n" : "<FALSE>\n");
}

int skew_product(std::pair< zaitsev::Point, zaitsev::Point > vects)
{
  return vects.first.x * vects.second.y - vects.first.y * vects.second.x;
}


generator::generator(const zaitsev::Polygon& base):
  points(base.points),
  pos(0)
{}

std::pair< zaitsev::Point, zaitsev::Point > generator::operator()()
{
  pos = (pos + 1) % points.size();
  return { points[pos], points[(pos + 1) % points.size()] };
}

double get_area(const zaitsev::Polygon& poly)
{
  using namespace std::placeholders;
  std::list< std::pair< zaitsev::Point, zaitsev::Point > > edges;
  generator gen(poly);
  std::generate_n(std::back_inserter(edges), poly.points.size(), gen);
  std::list< int > areas;
  std::transform(edges.begin(), edges.end(), std::back_inserter(areas), skew_product);
  return std::fabs(std::accumulate(areas.begin(), areas.end(), 0) / 2.0);
}

double cond_area_sum(const std::list< zaitsev::Polygon >& polys, std::function< bool(const zaitsev::Polygon&) > cond)
{
  std::list< zaitsev::Polygon >satisfy_cond;
  std::copy_if(polys.begin(), polys.end(), std::back_inserter(satisfy_cond), cond);
  std::list< double > areas;
  std::transform(satisfy_cond.begin(), satisfy_cond.end(), std::back_inserter(areas), get_area);
  return std::accumulate(areas.begin(), areas.end(), 0.0);
}

bool is_odd_size(const zaitsev::Polygon& poly)
{
  return poly.points.size() % 2 == 1;
}
bool is_even_size(const zaitsev::Polygon& poly)
{
  return poly.points.size() % 2 == 0;
}
bool is_equal_size(const zaitsev::Polygon& poly, size_t target)
{
  return poly.points.size() == target;
}
bool true_function(const zaitsev::Polygon& poly)
{
  return std::addressof(poly) == std::addressof(poly);
}
bool size_cmp(const zaitsev::Polygon& p1, const zaitsev::Polygon& p2)
{
  return p1.points.size() < p2.points.size();
}
bool area_cmp(const zaitsev::Polygon& p1, const zaitsev::Polygon& p2)
{
  return  get_area(p1) < get_area(p2);
}
bool out_of_bounds(std::pair< zaitsev::Point, zaitsev::Point > bounds, zaitsev::Point pt)
{
  return (pt.x < bounds.first.x || pt.x > bounds.second.x || pt.y < bounds.first.y || pt.y > bounds.second.y);
}

std::pair< zaitsev::Point, zaitsev::Point > frame_rect(const std::vector< zaitsev::Point >& pts)
{
  using namespace zaitsev;
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

std::pair< zaitsev::Point, zaitsev::Point > big_frame_rect(const std::list< zaitsev::Polygon >& poly)
{
  using namespace zaitsev;
  using rect_bounds = std::pair< Point, Point >;
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

