#include "commands.hpp"

void zaitsev::check_fail(std::istream& in)
{
  if (in.fail())
  {
    in.clear();
    in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
}

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
    auto functor = std::bind(extremum_area, plh::_1, plh::_2, max< double >);
    return out << std::accumulate(shapes.begin(), shapes.end(), get_area(*shapes.begin()), functor) << '\n';
  }
  if (!shapes.empty() && arg == "VERTEXES")
  {
    auto functor = std::bind(extremum_size, plh::_1, plh::_2, max< size_t >);
    return out << std::accumulate(shapes.begin(), shapes.end(), shapes.begin()->points.size(), functor) << '\n';
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
    auto functor = std::bind(extremum_area, plh::_1, plh::_2, min< double >);
    return out << std::accumulate(shapes.begin(), shapes.end(), get_area(*shapes.begin()), functor) << '\n';
  }
  if (!shapes.empty() && arg == "VERTEXES")
  {
    auto functor = std::bind(extremum_size, plh::_1, plh::_2, min< size_t >);
    return out << std::accumulate(shapes.begin(), shapes.end(), shapes.begin()->points.size(), functor) << '\n';
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
    auto functor = std::bind(cond_count, plh::_1, plh::_2, is_even_size);
    return out << std::accumulate(shapes.begin(), shapes.end(), 0ull, functor) << '\n';
  }
  if (arg == "ODD")
  {
    auto functor = std::bind(cond_count, plh::_1, plh::_2, is_odd_size);
    return out << std::accumulate(shapes.begin(), shapes.end(), 0ull, functor) << '\n';
  }

  size_t sz = std::stoull(arg);
  std::function< bool(const Polygon&) > cond = std::bind(is_equal_size, plh::_1, sz);
  std::function< size_t(size_t, const Polygon&) > functor = std::bind(cond_count, plh::_1, plh::_2, cond);
  return out << std::accumulate(shapes.begin(), shapes.end(), 0ull, functor) << '\n';
}

void zaitsev::lessarea_cmd(std::istream& in, std::ostream& out, std::list< Polygon>& shapes)
{
  Polygon sup;
  in >> sup;
  double sup_sz = get_area(sup);
  std::function< bool(const Polygon&) > cond = std::bind(less_area, plh::_1, sup_sz);
  std::function< size_t(size_t, const Polygon&) > functor = std::bind(cond_count, plh::_1, plh::_2, cond);
  out << std::accumulate(shapes.begin(), shapes.end(), 0ull, functor) << '\n';
}

void zaitsev::inframe_cmd(std::istream& in, std::ostream& out, std::list< Polygon>& shapes)
{
  Polygon sup;
  in >> sup;
  Point left_lower = std::accumulate(shapes.begin(), shapes.end(), Point{ 0,0 }, left_corner);
  Point right_upper = std::accumulate(shapes.begin(), shapes.end(), Point{ 0,0 }, right_corner);
  auto checker = std::bind(out_of_bounds, plh::_1, left_lower, right_upper, plh::_2);
  out << (std::accumulate(sup.points.begin(), sup.points.end(), 0ull, checker) == 0 ? "<TRUE>\n" : "<FALSE>\n");
}
