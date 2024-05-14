#include "commands.hpp"
#include <algorithm>
#include <iterator>
#include <numeric>
#include <functional>
#include <utility>

double novikov::cmd::AccumulateArea::operator()(double val, const Polygon& rhs)
{
  return func(val, rhs);
}

void novikov::cmd::area(const area_args_t& args, const poly_vec_t& vec, std::istream& in, std::ostream& out)
{
  std::string arg;
  in >> arg;

  AccumulateArea area_accumulator;

  try
  {
    size_t size = std::stoul(arg);
    if (size < 3)
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    using namespace std::placeholders;
    predicate_t acc_pred = std::bind(hasVertexesCount, _1, size);
    area_accumulator.func = std::bind(cmd::accAreaIf, _1, _2, acc_pred);
  }
  catch (const std::invalid_argument&)
  {
    area_accumulator = args.at(arg);
    if (!area_accumulator.empty_vector_support && vec.empty())
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
  }

  FormatGuard guard(out);
  out << std::setprecision(1) << std::fixed;
  out << std::accumulate(vec.cbegin(), vec.cend(), 0.0, area_accumulator) << "\n";
}

double novikov::cmd::accAreaIf(double val, const Polygon& rhs, predicate_t pred)
{
  return val + getArea(rhs) * pred(rhs);
}

double novikov::cmd::accAreaMean(double val, const Polygon& rhs, size_t size)
{
  return val + getArea(rhs) / size;
}

novikov::cmd::poly_vec_it_t novikov::cmd::Max::operator()(poly_vec_it_t begin, poly_vec_it_t end, comparator_t comp)
{
  return std::max_element(begin, end, comp);
}

novikov::cmd::poly_vec_it_t novikov::cmd::Min::operator()(poly_vec_it_t begin, poly_vec_it_t end, comparator_t comp)
{
  return std::min_element(begin, end, comp);
}

void novikov::cmd::minmax(const minmax_args_t& args, const poly_vec_t& vec, std::istream& in, std::ostream& out)
{
  if (vec.empty())
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  std::string arg;
  in >> arg;
  args.at(arg)(vec, out);
}

void novikov::cmd::count(const count_args_t& args, const poly_vec_t& vec, std::istream& in, std::ostream& out)
{
  std::string arg;
  in >> arg;

  std::function< bool(const Polygon&) > count_pred;

  try
  {
    size_t size = std::stoul(arg);
    if (size < 3)
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    count_pred = std::bind(hasVertexesCount, std::placeholders::_1, size);
  }
  catch (const std::invalid_argument&)
  {
    count_pred = args.at(arg);
  }

  FormatGuard guard(out);
  out << std::count_if(vec.cbegin(), vec.cend(), count_pred) << "\n";
}

novikov::Polygon novikov::cmd::EntryDuplicator::operator()(Polygon&& rhs)
{
  if (arg == rhs)
  {
    vec.push_back(rhs);
  }
  return rhs;
}

void novikov::cmd::echo(poly_vec_t& vec, std::istream& in, std::ostream& out)
{
  if (vec.empty())
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  Polygon arg;
  in >> arg;
  if (!in || in.peek() != '\n' || in.peek() != ' ')
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  size_t count = std::count(vec.cbegin(), vec.cend(), arg);
  FormatGuard guard(out);
  out << count << "\n";
  EntryDuplicator duplicator{ vec, arg };
  poly_vec_t temp;
  auto make_it = std::make_move_iterator< poly_vec_t::iterator >;
  std::transform(make_it(vec.begin()), make_it(vec.end()), std::back_inserter(temp), std::ref(duplicator));
  vec = std::move(temp);
}

void novikov::cmd::inFrame(const poly_vec_t& vec, std::istream& in, std::ostream& out)
{
  if (vec.empty())
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  Polygon arg;
  in >> arg;
  if (!in || in.peek() != '\n' || in.peek() != ' ')
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }

  int min_arg_x = minX(arg);
  int min_arg_y = minY(arg);
  int max_arg_x = maxX(arg);
  int max_arg_y = maxY(arg);

  Polygon rect = getFrameRect(vec);

  int min_rect_x = minX(rect);
  int min_rect_y = minY(rect);
  int max_rect_x = maxX(rect);
  int max_rect_y = maxY(rect);

  bool res = min_arg_x >= min_rect_x && max_arg_x <= max_rect_x && min_arg_y >= min_rect_y && max_arg_y <= max_rect_y;

  out << (res ? "<TRUE>" : "<FALSE>") << "\n";
}

novikov::Polygon novikov::cmd::getFrameRect(const poly_vec_t& vec)
{
  Polygon min_x_polygon = *std::min_element(vec.cbegin(), vec.cend(), comparePolygonsMinX);
  Polygon min_y_polygon = *std::min_element(vec.cbegin(), vec.cend(), comparePolygonsMinY);
  Polygon max_x_polygon = *std::max_element(vec.cbegin(), vec.cend(), comparePolygonsMaxX);
  Polygon max_y_polygon = *std::max_element(vec.cbegin(), vec.cend(), comparePolygonsMaxY);

  int min_x = minX(min_x_polygon);
  int min_y = minY(min_y_polygon);
  int max_x = maxX(max_x_polygon);
  int max_y = maxY(max_y_polygon);

  return Polygon{ { { min_x, min_y }, { min_x, max_y }, { max_x, max_y }, { max_x, min_y } } };
}
