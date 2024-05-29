#include "commands.hpp"

#include <algorithm>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iterator>
#include <map>
#include <numeric>
#include <stdexcept>
#include <string>
#include "point.hpp"
#include "polygon.hpp"
#include "streamGuard.hpp"

namespace ibragimov
{
  ibragimov::command getCommand(const std::string& input, const mapOfCommands& subcommands);
  std::vector< ibragimov::Polygon > filter(const std::vector< Polygon >& values, const predicate& predicate);
  bool isPermutation(const Polygon& lhs, const Polygon& rhs);
  bool isContainingRightAngles(const Polygon& rhs);
}

void ibragimov::getArea(const mapOfCommands& subcommands, const std::vector< Polygon >& values, std::istream& in, std::ostream& out)
{
  std::string input = "";
  in >> input;
  command command;
  try
  {
    command = getCommand(input, subcommands);
  }
  catch (const std::exception&)
  {
    size_t numOfVertexes = std::stoull(input);
    if (numOfVertexes < 3)
    {
      throw std::invalid_argument("Polygons with less than 3 points don't exist");
    }
    using namespace std::placeholders;
    predicate predicate = std::bind(std::equal_to< size_t >{}, std::bind(getSize, _1), numOfVertexes);
    command = std::bind(outputDouble, _2, std::bind(accumAreaIf, _1, predicate));
  }

  command(values, out);
}
void ibragimov::find(const mapOfCommands& subcommands, const std::vector< Polygon >& values, std::istream& in, std::ostream& out)
{
  if (values.size() == 0)
  {
    throw std::out_of_range("Zero polygons to work with");
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
  try
  {
    command = getCommand(input, subcommands);
  }
  catch (const std::exception&)
  {
    size_t numOfVertexes = std::stoull(input);
    if (numOfVertexes < 3)
    {
      throw std::invalid_argument("Polygons with less than 3 points don't exist");
    }
    using namespace std::placeholders;
    predicate predicate = std::bind(std::equal_to< size_t >{}, std::bind(getSize, _1), numOfVertexes);
    command = std::bind(outputULL, _2, std::bind(countIf, _1, predicate));
  }

  command(values, out);
}
void ibragimov::countPerms(const std::vector< Polygon >& values, std::istream& in, std::ostream& out)
{
  Polygon input;
  in >> input;

  using namespace std::placeholders;
  predicate predicate = std::bind(std::equal_to< size_t >{}, std::bind(getSize, _1), input.points.size());
  std::vector< Polygon > correct(filter(values, predicate));
  if (correct.size() == 0)
  {
    throw std::out_of_range("Zero polygons to work with");
  }

  predicate = std::bind(isPermutation, input, _1);
  command command = std::bind(outputULL, _2, std::bind(countIf, _1, predicate));
  command(correct, out);
}
void ibragimov::countRightshapes(const std::vector< Polygon >& values, std::ostream& out)
{
  if (values.size() == 0)
  {
    throw std::out_of_range("Zero polygons to work with");
  }
  outputULL(out, countIf(values, isContainingRightAngles));
}

double ibragimov::accumArea(const std::vector< Polygon >& values)
{
  std::vector< double > areas(values.size());
  std::transform(values.cbegin(), values.cend(), areas.begin(), calculateArea);
  return std::accumulate(std::cbegin(areas), std::cend(areas), 0.0);
}
double ibragimov::accumAreaIf(const std::vector< Polygon >& values, const predicate& predicate)
{
  return accumArea(filter(values, predicate));
}
double ibragimov::accumMeanArea(const std::vector< Polygon >& values)
{
  if (values.size() == 0)
  {
    throw std::out_of_range("Zero polygons to work with");
  }
  return accumArea(values) / values.size();
}
ibragimov::Polygon ibragimov::findMax(const std::vector< Polygon >& values, const comparator& comparator)
{
  return *std::max_element(values.cbegin(), values.cend(), comparator);
}
ibragimov::Polygon ibragimov::findMin(const std::vector< Polygon >& values, const comparator& comparator)
{
  return *std::min_element(values.cbegin(), values.cend(), comparator);
}
size_t ibragimov::countIf(const std::vector< Polygon >& values, const predicate& predicate)
{
  return std::count_if(values.cbegin(), values.cend(), predicate);
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
    StreamGuard sguard(out);
    out << std::fixed << std::setprecision(1);
    out << value << '\n';
  }
}
void ibragimov::outputArea(std::ostream& out, const Polygon& value)
{
  std::ostream::sentry guard(out);
  if (guard)
  {
    StreamGuard sguard(out);
    out << std::fixed << std::setprecision(1);
    out << calculateArea(value) << '\n';
  }
}

ibragimov::command ibragimov::getCommand(const std::string& input, const mapOfCommands& subcommands)
{
  command command;
  command = subcommands.at(input);
  return command;
}
std::vector< ibragimov::Polygon > ibragimov::filter(const std::vector< Polygon >& values, const predicate& predicate)
{
  size_t size = std::count_if(values.cbegin(), values.cend(), predicate);
  std::vector< Polygon > temp(size);
  std::copy_if(values.cbegin(), values.cend(), temp.begin(), predicate);
  return temp;
}
bool ibragimov::isPermutation(const Polygon& lhs, const Polygon& rhs)
{
  using namespace std::placeholders;
  auto compareX = std::bind(std::equal_to< int >{}, std::bind(getX, _1), std::bind(getX, _2));
  auto compareY = std::bind(std::equal_to< int >{}, std::bind(getY, _1), std::bind(getY, _2));
  auto comparePoints = std::bind(std::logical_and<>{}, std::bind(compareX, _1, _2), std::bind(compareY, _1, _2));
  return std::is_permutation(rhs.points.cbegin(), rhs.points.cend(),
      lhs.points.cbegin(), lhs.points.cend(), comparePoints);
}
bool ibragimov::isContainingRightAngles(const Polygon& rhs)
{
  std::vector< Point > points(rhs.points);
  points.push_back(points[0]);
  std::transform(next(points.cbegin()), points.cend(), points.cbegin(), points.begin(), calculateSide);
  points.back() = points[0];

  std::vector< double > angles(points.size());
  std::transform(next(points.cbegin()), points.cend(), points.cbegin(), angles.begin(), calculateAngle);
  using namespace std::placeholders;
  auto isRightAngle = std::bind(std::equal_to< double >{}, _1, std::atan2(1, 0));
  return std::any_of(angles.cbegin(), angles.cend(), isRightAngle);
}
