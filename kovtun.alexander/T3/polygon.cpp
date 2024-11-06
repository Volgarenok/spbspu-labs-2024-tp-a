#include "polygon.hpp"


std::istream & kovtun::operator>>(std::istream & in, kovtun::Polygon & polygon)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  using dl = kovtun::DelimiterI;

  polygon.points.clear();
  size_t size = 0;
  in >> size;
  if (size < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  for (size_t i = 0; i < size; ++i)
  {
    kovtun::Point point = {};
    in >> dl{'('} >> point.x >> dl{';'} >> point.y >> dl{')'};
    polygon.points.push_back(point);
  }

  return in;
}

double kovtun::right_cross::operator()(const kovtun::Point & first, const kovtun::Point & second) const
{
  return first.x * second.y;
}

double kovtun::left_cross::operator()(const kovtun::Point & first, const kovtun::Point & second) const
{
  return first.y * second.x;
}

double kovtun::getArea(const kovtun::Polygon & polygon)
{
  auto points = polygon.points;

  std::vector< kovtun::Point > rotatedPoints(points.size());
  std::rotate_copy(points.cbegin(), points.cbegin() + 1, points.cend(), rotatedPoints.begin());

  std::vector< double > positiveAccumulator(points.size());
  std::transform(points.cbegin(), points.cend(), rotatedPoints.cbegin(), positiveAccumulator.begin(), right_cross{});

  std::vector< double > negativeAccumulator(points.size());
  std::transform(points.cbegin(), points.cend(), rotatedPoints.cbegin(), negativeAccumulator.begin(), left_cross{});

  double positivePart = std::accumulate(positiveAccumulator.cbegin(), positiveAccumulator.cend(), 0.0);
  double negativePart = std::accumulate(negativeAccumulator.cbegin(), negativeAccumulator.cend(), 0.0);

  double area = std::abs(positivePart - negativePart) / 2.0;
  return area;
}

bool kovtun::operator==(const kovtun::Polygon & first, const kovtun::Polygon & second)
{
  if (first.points.size() != second.points.size())
  {
    return false;
  }

  return std::equal(first.points.cbegin(), first.points.cend(), second.points.cbegin());
}

bool kovtun::operator==(const kovtun::Point & first, const kovtun::Point & second)
{
  return first.x == second.x && first.y == second.y;
}
