#include "commands_temp.hpp"
#include <algorithm>
#include <iterator>
#include <numeric>
#include <functional>
#include <utility>
#include <cstdlib>
#include "polygon_temp.hpp"

void zhakha::cmd::area(const area_args_t& args, const poly_vec_t& vec, std::istream& in, std::ostream& out)
{
  std::string arg;
  in >> arg;

  AreaCalculator area_calculator;

  try
  {
    size_t size = std::strtoul(arg.c_str(), nullptr, 10);

    if (size < 3)
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }

    using namespace std::placeholders;
    predicate_t pred = std::bind(hasVertexesCount, _1, size);
    area_calculator.calculate = std::bind(calculateAreaIf, _1, pred);
  }
  catch (const std::invalid_argument&)
  {
    area_calculator = args.at(arg);

    if (!area_calculator.empty_vector_support && vec.empty())
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
  }

  std::vector< double > areas(vec.size());
  std::transform(vec.cbegin(), vec.cend(), areas.begin(), area_calculator.calculate);

  StreamGuard guard(out);
  out << std::setprecision(1) << std::fixed;
  out << std::accumulate(areas.cbegin(), areas.cend(), 0.0) << "\n";
}

void zhakha::cmd::minmax(const minmax_args_t& args, const poly_vec_t& vec, std::istream& in, std::ostream& out)
{
  if (vec.empty())
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }

  std::string arg;
  in >> arg;
  args.at(arg)(vec, out);
}

void zhakha::cmd::count(const count_args_t& args, const poly_vec_t& vec, std::istream& in, std::ostream& out)
{
  std::string arg;
  in >> arg;

  std::function<bool(const Polygon&)> count_pred;

  try
  {
    size_t size = std::strtoul(arg.c_str(), nullptr, 10);

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

  StreamGuard guard(out);
  out << std::count_if(vec.cbegin(), vec.cend(), count_pred) << "\n";
}

void zhakha::cmd::echo(poly_vec_t& vec, std::istream& in, std::ostream& out)
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

  EntryDuplicator duplicator{ vec, arg };
  poly_vec_t temp;
  temp.reserve(vec.size() + count);
  auto make_it = std::make_move_iterator< poly_vec_t::iterator >;
  std::transform(make_it(vec.begin()), make_it(vec.end()), std::back_inserter(temp), std::ref(duplicator));
  vec = std::move(temp);

  StreamGuard guard(out);
  out << count << "\n";
}

void zhakha::cmd::inFrame(const poly_vec_t& vec, std::istream& in, std::ostream& out)
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

  auto minmax_arg_x = std::minmax_element(arg.points.cbegin(), arg.points.cend(), comparePointsX);
  auto minmax_arg_y = std::minmax_element(arg.points.cbegin(), arg.points.cend(), comparePointsY);

  Polygon rect = getFrameRect(vec);

  auto minmax_rect_x = std::minmax_element(rect.points.cbegin(), rect.points.cend(), comparePointsX);
  auto minmax_rect_y = std::minmax_element(rect.points.cbegin(), rect.points.cend(), comparePointsY);

  bool res = isLayingIn(minmax_arg_x, minmax_arg_y, minmax_rect_x, minmax_rect_y);

  out << (res ? "<TRUE>" : "<FALSE>") << "\n";
}

double zhakha::calculateAreaIf(const Polygon& polygon, predicate_t pred)
{
  return getArea(polygon) * pred(polygon);
}

double zhakha::calculateMeanArea(const Polygon& polygon, size_t size)
{
  return getArea(polygon) / size;
}

zhakha::poly_vec_it_t zhakha::Max::operator()(poly_vec_it_t begin, poly_vec_it_t end, comparator_t comp)
{
  return std::max_element(begin, end, comp);
}

zhakha::poly_vec_it_t zhakha::Min::operator()(poly_vec_it_t begin, poly_vec_it_t end, comparator_t comp)
{
  return std::min_element(begin, end, comp);
}

zhakha::Polygon zhakha::EntryDuplicator::operator()(Polygon&& rhs)
{
  if (arg == rhs)
  {
    vec.emplace_back(rhs);
  }

  return rhs;
}

zhakha::Polygon zhakha::getFrameRect(const poly_vec_t& vec)
{
  Polygon min_x_polygon = *std::min_element(vec.cbegin(), vec.cend(), comparePolygonsMinX);
  Polygon min_y_polygon = *std::min_element(vec.cbegin(), vec.cend(), comparePolygonsMinY);
  Polygon max_x_polygon = *std::min_element(vec.cbegin(), vec.cend(), comparePolygonsMaxX);
  Polygon max_y_polygon = *std::min_element(vec.cbegin(), vec.cend(), comparePolygonsMaxY);

  int min_x = std::min_element(min_x_polygon.points.cbegin(), min_x_polygon.points.cend(), comparePointsX)->x;
  int min_y = std::min_element(min_y_polygon.points.cbegin(), min_y_polygon.points.cend(), comparePointsY)->y;
  int max_x = std::max_element(max_x_polygon.points.cbegin(), max_x_polygon.points.cend(), comparePointsX)->x;
  int max_y = std::max_element(max_y_polygon.points.cbegin(), max_y_polygon.points.cend(), comparePointsY)->y;

  return Polygon{{{ min_x, min_y }, { min_x, max_y }, { max_x, max_y }, { max_x, min_y }}};
}
