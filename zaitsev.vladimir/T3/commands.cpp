#include "commands.hpp"
#include <iterator>
#include <algorithm>
#include <functional>
#include <string>
#include <iomanip>
#include <numeric>
#include <type_traits>
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

std::ostream& zaitsev::extr_cmd(bool is_min, std::istream& in, std::ostream& out, std::list< Polygon >& shapes)
{
  std::string arg;
  in >> arg;
  in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  if (!shapes.empty() && arg == "AREA")
  {
    StreamGuard guard(out);
    out << std::fixed << std::setprecision(1);
    auto extrems = std::minmax_element(shapes.begin(), shapes.end(), area_cmp);
    return out << get_area(*(is_min ? extrems.first : extrems.second)) << '\n';
  }
  if (!shapes.empty() && arg == "VERTEXES")
  {
    auto extrems = std::minmax_element(shapes.begin(), shapes.end(), size_cmp);
    return out << (is_min ? extrems.first : extrems.second)->points.size() << '\n';
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
