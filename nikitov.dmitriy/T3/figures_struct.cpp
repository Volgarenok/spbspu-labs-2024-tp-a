#include "figures_struct.hpp"
#include <istream>
#include <iterator>
#include <limits>
#include <functional>
#include <algorithm>
#include <numeric>
#include <delimiter.hpp>

double getArea(const nikitov::Point& first, const nikitov::Point& second, const nikitov::Point& third)
{
  return 0.5 * std::abs((first.x - third.x) * (second.y - third.y) - (second.x - third.x) * (first.y - third.y));
}

struct AreasGenerator
{
  std::vector< nikitov::Point >::const_iterator firstIterator;
  std::vector< nikitov::Point >::const_iterator secondIterator;
  double operator()()
  {
    return getArea(*firstIterator, *(++secondIterator), *secondIterator);
  }
};

double nikitov::getPolygonArea(const Polygon& figure)
{
  auto iterator = figure.points.cbegin();
  AreasGenerator generator({ iterator++, iterator });
  std::vector< double > areas(figure.points.size() - 2);
  std::generate_n(areas.begin(), figure.points.size() - 2, generator);
  return std::accumulate(areas.cbegin(), areas.cend(), 0.0);
}

bool nikitov::operator==(const Point& lhs, const Point& rhs)
{
  return lhs.x == rhs.x && lhs.y == rhs.y;
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
  std::vector< Point > points(pointsNum);
  std::copy_n(input_it_t{ input }, pointsNum, points.begin());
  if (input)
  {
    value.points = std::move(points);
  }

  return input;
}
