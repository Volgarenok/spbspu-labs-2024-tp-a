#include "commands.hpp"
#include <iterator>
#include <algorithm>
#include <functional>
#include <string>
#include <iomanip>
#include <numeric>
#include <stream_guard.hpp>
#include "detail.hpp"

std::ostream& zaitsev::area_cmd(std::istream& in, std::ostream& out, std::list< Polygon>& shapes)
{
  StreamGuard guard(out);
  out << std::fixed << std::setprecision(1);
  std::string arg;
  in >> arg;
  in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  if (arg == "EVEN")
  {
    auto functor = std::bind(cond_area_sum, plh::_1, plh::_2, is_even_size);
    return out << std::accumulate(shapes.begin(), shapes.end(), 0.0, functor) << '\n';
  }
  if (arg == "ODD")
  {
    auto functor = std::bind(cond_area_sum, plh::_1, plh::_2, is_odd_size);
    return out << std::accumulate(shapes.begin(), shapes.end(), 0.0, functor) << '\n';
  }
  if (!shapes.empty() && arg == "MEAN")
  {
    auto functor = std::bind(cond_area_sum, plh::_1, plh::_2, get_area);
    return out << std::accumulate(shapes.begin(), shapes.end(), 0.0, functor) / shapes.size() << '\n';
  }
  size_t sz = std::stoull(arg);
  if (sz < 3)
  {
    throw std::invalid_argument("");
  }
  std::function< bool(const Polygon&) > cond = std::bind(is_equal_size, plh::_1, sz);
  std::function< double(double, const Polygon&) > functor = std::bind(cond_area_sum, plh::_1, plh::_2, cond);
  return out << std::accumulate(shapes.begin(), shapes.end(), 0.0, functor) << '\n';
}

std::ostream& zaitsev::max_cmd(std::istream& in, std::ostream& out, std::list< Polygon>& shapes)
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

std::ostream& zaitsev::min_cmd(std::istream& in, std::ostream& out, std::list< Polygon>& shapes)
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
  Point left_lower = std::accumulate(shapes.begin(), shapes.end(), shapes.begin()->points[0], left_corner);
  Point right_upper = std::accumulate(shapes.begin(), shapes.end(), shapes.begin()->points[0], right_corner);
  std::function< bool(Point) > cond = std::bind(out_of_bounds, left_lower, right_upper, plh::_1);
  return out << (std::find_if(p.points.begin(), p.points.end(), cond) == p.points.end() ? "<TRUE>\n" : "<FALSE>\n");
}
