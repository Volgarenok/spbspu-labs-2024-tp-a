#include "figures_struct.hpp"
#include <istream>
#include <iterator>
#include <limits>
#include <functional>
#include <algorithm>
#include <numeric>
#include <delimiter.hpp>

double countArea(const nikitov::Point& first, const nikitov::Point& second, const nikitov::Point& third)
{
  return 0.5 * std::abs((first.x - third.x) * (second.y - third.y) - (second.x - third.x) * (first.y - third.y));
}

bool nikitov::Point::operator==(const Point& other) const
{
  return (x == other.x) && (y == other.y);
}

double nikitov::Polygon::getArea() const
{
  using namespace std::placeholders;
  auto iterator = points.cbegin();
  AccumulateArea accum({ *iterator, *(++iterator) });
  return std::accumulate(++iterator, points.cend(), 0.0, accum);
}

double nikitov::AccumulateArea::operator()(double result, const Point& third)
{
  result += countArea(first, second, third);
  second = third;
  return result;
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
    return input;
  }

  using input_it_t = std::istream_iterator< Point >;
  std::vector< Point > points;
  std::copy_n(input_it_t{ input }, pointsNum, std::back_inserter(points));
  if (!input.eof())
  {
    if (input.fail())
    {
      value.points.clear();
      input.clear();
    }
    else
    {
      value.points = std::move(points);
    }
  }
  input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');

  return input;
}
