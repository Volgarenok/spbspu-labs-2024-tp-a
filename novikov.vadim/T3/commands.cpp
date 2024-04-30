#include "commands.hpp"
#include <algorithm>
#include <iomanip>
#include <numeric>
#include <functional>
#include <formatGuard.hpp>
#include "polygon.hpp"
#include "predicates.hpp"

void novikov::cmd::area(const area_args_t& args, const poly_vec_t& vec, std::istream& in, std::ostream& out)
{
  std::string arg;
  in >> arg;

  std::function< double(double, const Polygon&) > area_accumulator;

  try
  {
    std::size_t size = std::stoul(arg);
    if (size < 3)
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    using namespace std::placeholders;
    Predicate acc_pred = std::bind(vertexes_count, _1, size);
    area_accumulator = std::bind(cmd::acc_area_if, _1, _2, acc_pred);
  }
  catch (const std::invalid_argument&)
  {
    area_accumulator = args.at(arg);
  }

  FormatGuard guard(out);
  out << std::setprecision(1) << std::fixed;
  out << std::accumulate(vec.cbegin(), vec.cend(), 0.0, area_accumulator) << "\n";
}

double novikov::cmd::acc_area_if(double val, const Polygon& rhs, Predicate pred)
{
  return pred(rhs) ? val + get_area(rhs) : val;
}

double novikov::cmd::acc_area_mean(double val, const Polygon& rhs, std::size_t size)
{
  return val + get_area(rhs) / size;
}

void novikov::cmd::max(const max_args_t& args, const poly_vec_t& vec, std::istream& in, std::ostream& out)
{
  if (vec.empty())
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  std::string arg;
  in >> arg;
  args.at(arg)(vec, out);
}

void novikov::cmd::max_area(const poly_vec_t& vec, std::ostream& out)
{
  FormatGuard guard(out);
  auto res = std::max_element(vec.cbegin(), vec.cend(), compare_areas);
  out << std::setprecision(1) << std::fixed;
  out << get_area(*res) << "\n";
}

void novikov::cmd::max_vertexes(const poly_vec_t& vec, std::ostream& out)
{
  FormatGuard guard(out);
  auto res = std::max_element(vec.cbegin(), vec.cend(), compare_vertexes);
  out << res->points.size() << "\n";
}

void novikov::cmd::min(const min_args_t& args, const poly_vec_t& vec, std::istream& in, std::ostream& out)
{
  if (vec.empty())
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  std::string arg;
  in >> arg;
  args.at(arg)(vec, out);
}

void novikov::cmd::min_area(const poly_vec_t& vec, std::ostream& out)
{
  FormatGuard guard(out);
  auto res = std::min_element(vec.cbegin(), vec.cend(), compare_areas);
  out << std::setprecision(1) << std::fixed;
  out << get_area(*res) << "\n";
}

void novikov::cmd::min_vertexes(const poly_vec_t& vec, std::ostream& out)
{
  FormatGuard guard(out);
  auto res = std::min_element(vec.cbegin(), vec.cend(), compare_vertexes);
  out << res->points.size() << "\n";
}

void novikov::cmd::count(const count_args_t& args, const poly_vec_t& vec, std::istream& in, std::ostream& out)
{
  std::string arg;
  in >> arg;

  std::function< bool(const Polygon&) > count_pred;

  try
  {
    std::size_t size = std::stoul(arg);
    if (size < 3)
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    count_pred = std::bind(vertexes_count, std::placeholders::_1, size);
  }
  catch (const std::invalid_argument&)
  {
    count_pred = args.at(arg);
  }

  FormatGuard guard(out);
  out << std::count_if(vec.cbegin(), vec.cend(), count_pred) << "\n";
}

void novikov::cmd::echo(poly_vec_t& vec, std::istream& in, std::ostream& out)
{
  if (vec.empty())
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  Polygon arg;
  in >> arg;
  if (!in)
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  std::size_t count = std::count(vec.cbegin(), vec.cend(), arg);
  FormatGuard guard(out);
  out << count << "\n";
  std::vector< Polygon > temp;
  for (auto it = vec.cbegin(); it != vec.cend(); ++it)
  {
    temp.push_back(*it);
    if (*it == arg)
    {
      temp.push_back(*it);
    }
  }
  vec = std::move(temp);
}

void novikov::cmd::in_frame(const poly_vec_t& vec, std::istream& in, std::ostream& out)
{
  if (vec.empty())
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  Polygon arg;
  in >> arg;
  if (!in)
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }

  int min_arg_x = min_x(arg);
  int min_arg_y = min_y(arg);
  int max_arg_x = max_x(arg);
  int max_arg_y = max_x(arg);

  Polygon rect = get_frame_rect(vec);

  int min_rect_x = min_x(rect);
  int min_rect_y = min_y(rect);
  int max_rect_x = max_x(rect);
  int max_rect_y = max_y(rect);

  bool res = min_arg_x >= min_rect_x && max_arg_x <= max_rect_x && min_arg_y >= min_rect_y && max_arg_y <= max_rect_y;

  out << (res ? "<TRUE>" : "<FALSE>") << "\n";
}

novikov::Polygon novikov::cmd::get_frame_rect(const poly_vec_t& vec)
{
  Polygon min_x_polygon = *std::min_element(vec.cbegin(), vec.cend(), compare_polygons_min_x);
  Polygon min_y_polygon = *std::min_element(vec.cbegin(), vec.cend(), compare_polygons_min_y);
  Polygon max_x_polygon = *std::max_element(vec.cbegin(), vec.cend(), compare_polygons_max_x);
  Polygon max_y_polygon = *std::max_element(vec.cbegin(), vec.cend(), compare_polygons_max_y);

  int minx = min_x(min_x_polygon);
  int miny = min_y(min_y_polygon);
  int maxx = max_x(max_x_polygon);
  int maxy = max_y(max_y_polygon);

  return Polygon{ { { minx, miny }, { minx, maxy }, { maxx, maxy }, { maxx, miny } } };
}
