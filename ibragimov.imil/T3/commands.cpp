#include "commands.hpp"

#include <algorithm>
#include <cmath>
#include <exception>
#include <functional>
#include <iomanip>
#include <iterator>
#include <map>
#include <numeric>
#include <string>
#include "point.hpp"
#include "polygon.hpp"
#include <streamGuard.hpp>

void ibragimov::getArea(const mapOfCommands& subcommands, const std::vector< Polygon >& values, std::istream& in, std::ostream& out)
{
  std::string input = "";
  in >> input;
  command command;
  if (detail::isCorrectNumber(input))
  {
    using namespace std::placeholders;
    predicate predicate = std::bind(std::equal_to< size_t >{}, std::bind(getSize, _1), std::stoull(input));
    command = std::bind(outputDouble, _2, std::bind(sumAreaIf, _1, predicate));
  }
  else
  {
    command = getCommand(input, subcommands);
  }

  command(values, out);
}
void ibragimov::find(const mapOfCommands& subcommands, const std::vector< Polygon >& values, std::istream& in, std::ostream& out)
{
  if (values.size() == 0)
  {
    throw std::exception();
  }

  std::string input = "";
  in >> input;
  command command;
  command = getCommand(input, subcommands);

  command(values, out);
}
void ibragimov::count(const mapOfCommands& subcommands, const std::vector< Polygon >& values, std::istream& in, std::ostream& out)
{
  std::string input = "";
  in >> input;
  command command;
  if (detail::isCorrectNumber(input))
  {
    using namespace std::placeholders;
    predicate predicate = std::bind(std::equal_to< size_t >{}, std::bind(getSize, _1), std::stoull(input));
    command = std::bind(outputULL, _2, std::bind(countIf, _1, predicate));
  }
  else
  {
    command = getCommand(input, subcommands);
  }

  command(values, out);
}
void ibragimov::countPerms(const std::vector< Polygon >& values, std::istream& in, std::ostream& out)
{
  Polygon input;
  in >> input;

  std::vector< Polygon > correct = {};
  using namespace std::placeholders;
  predicate predicate = std::bind(std::equal_to< size_t >{}, std::bind(getSize, _1), input.points.size());
  std::copy_if(values.cbegin(), values.cend(), std::back_inserter(correct), predicate);
  if (correct.size() == 0)
  {
    throw std::exception();
  }

  predicate = std::bind(isPermutation, input, _1);
  command command = std::bind(outputULL, _2, std::bind(countIf, _1, predicate));
  command(correct, out);
}
void ibragimov::countRightshapes(const std::vector< Polygon >& values, std::ostream& out)
{
  if (values.size() == 0)
  {
    throw std::exception();
  }
  outputULL(out, countIf(values, isContainingRightAngles));
}

ibragimov::command ibragimov::getCommand(const std::string& input, const mapOfCommands& subcommands)
{
  command command;
  command = subcommands.at(input);
  return command;
}

double ibragimov::accumArea(const std::vector< Polygon >& values)
{
  std::vector< double > areas = {};
  std::transform(values.cbegin(), values.cend(), std::back_inserter(areas), calculateArea);
  return std::accumulate(std::cbegin(areas), std::cend(areas), 0.0);
}
double ibragimov::accumAreaIf(const std::vector< Polygon >& values, const predicate& predicate)
{
  std::vector< Polygon > temp = {};
  std::copy_if(std::cbegin(values), std::cend(values), std::back_inserter(temp), predicate);
  return accumArea(temp);
}
double ibragimov::accumMeanArea(const std::vector< Polygon >& values)
{
  if (values.size() == 0)
  {
    throw std::exception();
  }
  return accumArea(values) / values.size();
}
ibragimov::Polygon ibragimov::findMax(const std::vector< Polygon >& values, const comparator& comparator)
{
  return *std::max_element(std::cbegin(values), std::cend(values), comparator);
}
ibragimov::Polygon ibragimov::findMin(const std::vector< Polygon >& values, const comparator& comparator)
{
  return *std::min_element(std::cbegin(values), std::cend(values), comparator);
}
size_t ibragimov::countIf(const std::vector< Polygon >& values, const predicate& predicate)
{
  return std::count_if(std::cbegin(values), std::cend(values), predicate);
}
bool ibragimov::isPermutation(const Polygon& lhs, const Polygon& rhs)
{
  using namespace std::placeholders;
  auto compareX = std::bind(std::equal_to< int >{}, std::bind(getX, _1), std::bind(getX, _2));
  auto compareY = std::bind(std::equal_to< int >{}, std::bind(getY, _1), std::bind(getY, _2));
  auto comparePoints = std::bind(std::logical_and<>{}, std::bind(compareX, _1, _2), std::bind(compareY, _1, _2));
  return std::is_permutation(std::cbegin(rhs.points), std::cend(rhs.points),
      std::cbegin(lhs.points), std::cend(lhs.points), comparePoints);
}
bool ibragimov::isContainingRightAngles(const ibragimov::Polygon& rhs)
{
  std::vector< Point > points = {};
  std::copy(rhs.points.cbegin(), rhs.points.cend(), std::back_inserter(points));
  points.push_back(points[0]);

  std::transform(next(points.cbegin()), points.cend(), points.cbegin(), points.begin(), calculateSide);
  points.back() = points[0];

  std::vector< double > angles = {};
  std::transform(next(points.cbegin()), points.cend(), points.cbegin(), std::back_inserter(angles), calculateAngle);

  using namespace std::placeholders;
  auto isRightAngle = std::bind(std::equal_to< double >{}, _1, std::atan2(1, 0));
  return std::any_of(angles.cbegin(), angles.cend(), isRightAngle);
}

void ibragimov::outputULL(std::ostream& out, const size_t& value)
{
  std::ostream::sentry guard(out);
  if (guard)
  {
    out << value << '\n';
  }
}
void ibragimov::outputVertexes(std::ostream& out, const Polygon& value)
{
  std::ostream::sentry guard(out);
  if (guard)
  {
    out << getSize(value) << '\n';
  }
}
void ibragimov::outputDouble(std::ostream& out, const double& value)
{
  std::ostream::sentry guard(out);
  if (guard)
  {
    detail::StreamGuard sguard(out);
    out << std::fixed << std::setprecision(1);
    out << value << '\n';
  }
}
void ibragimov::outputArea(std::ostream& out, const Polygon& value)
{
  std::ostream::sentry guard(out);
  if (guard)
  {
    detail::StreamGuard sguard(out);
    out << std::fixed << std::setprecision(1);
    out << calculateArea(value) << '\n';
  }
}

bool ibragimov::detail::isCorrectNumber(const std::string& value)
{
  if (std::all_of(value.cbegin(), value.cend(), isdigit))
  {
    if (std::stoull(value) < 3)
    {
      throw std::exception();
    }
    return true;
  }
  return false;
}
