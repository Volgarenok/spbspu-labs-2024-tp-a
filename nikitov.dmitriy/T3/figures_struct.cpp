#include "figures_struct.hpp"
#include <istream>
#include <iterator>
#include <limits>
#include <functional>
#include <algorithm>
#include <numeric>
#include <delimiter.hpp>

bool nikitov::Point::operator==(const Point& other) const
{
  return (x == other.x) && (y == other.y);
}

double countArea(const nikitov::Point& first, const nikitov::Point& second, const nikitov::Point& third)
{
  return 0.5 * std::abs((first.x - third.x) * (second.y - third.y) - (second.x - third.x) * (first.y - third.y));
}

struct AccumulateArea
{
  nikitov::Point first;
  nikitov::Point second;
  double operator()(double result, const nikitov::Point& third);
};

double AccumulateArea::operator()(double result, const nikitov::Point& third)
{
  result += countArea(first, second, third);
  second = third;
  return result;
}

double nikitov::getArea(const nikitov::Polygon& figure)
{
  using namespace std::placeholders;
  auto iterator = figure.points.cbegin();
  AccumulateArea accum({ *iterator, *(++iterator) });
  return std::accumulate(++iterator, figure.points.cend(), 0.0, accum);
}

std::istream& nikitov::operator>>(std::istream& input, Point& value)
{
  std::istream::sentry guard(input);
  if (!guard)
  {
    return input;
  }
  using DelChar = DelimiterChar;
  input >> DelChar({'('}) >> value.x >> DelChar({';'}) >> value.y >> DelChar({')'});

  return input;
}

std::istream& nikitov::operator>>(std::istream& input, Polygon& value)
{
  std::istream::sentry guard(input);
  if (!guard)
  {
    return input;
  }
  size_t pointsNum = {};
  input >> pointsNum;
  if (pointsNum < 3)
  {
    input.setstate(std::ios::failbit);
  }

  using input_it_t = std::istream_iterator< Point >;
  std::vector< Point > points;
  std::copy_n(input_it_t{ input }, pointsNum, std::back_inserter(points));
  if (input)
  {
    value.points = std::move(points);
  }

  return input;
}
