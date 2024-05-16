#include "polygon.hpp"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <numeric>
#include "delimiter.hpp"
#include "predicates.hpp"
#include "functors.hpp"

std::istream & erohin::operator>>(std::istream & input, Point & point)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  Point temp;
  using del = IgnoredCaseDelimiter;
  input >> del{'('} >> point.x >> del{';'} >> point.y >> del{')'};
  if (!input)
  {
    point = temp;
  }
  return input;
}

std::ostream & erohin::operator<<(std::ostream & output, const Point & point)
{
  std::ostream::sentry sentry(output);
  if (!sentry)
  {
    return output;
  }
  output << '(' << point.x << ';' << point.y << ')';
  return output;
}

std::istream & erohin::operator>>(std::istream & input, Polygon & polygon)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  size_t count = 0;
  input >> count;
  std::vector< Point > temp;
  temp.reserve(count);
  std::copy_n(
    std::istream_iterator< Point >(input),
    count,
    std::back_inserter(temp)
  );
  if (input)
  {
    polygon.points = std::move(temp);
  }
  return input;
}

std::ostream & erohin::operator<<(std::ostream & output, const Polygon & polygon)
{
  std::ostream::sentry sentry(output);
  if (!sentry)
  {
    return output;
  }
  output << polygon.points.size() << " ";
  std::copy(
    polygon.points.cbegin(),
    polygon.points.cend(),
    std::ostream_iterator< Point >(output, " ")
  );
  return output;
}

std::pair< erohin::Point, erohin::Point > erohin::getFrameRect(const Polygon & polygon)
{
  if (polygon.points.empty())
  {
    throw std::logic_error("Cannot find frame rectangle of empty polygon");
  }
  auto x_pair = std::minmax_element(polygon.points.cbegin(), polygon.points.cend(), isLessByX);
  auto y_pair = std::minmax_element(polygon.points.cbegin(), polygon.points.cend(), isLessByY);
  return std::make_pair(Point{ x_pair.first->x, y_pair.first->y }, Point{ x_pair.second->x, y_pair.second->y });
}

std::pair< erohin::Point, erohin::Point > erohin::getFrameRect(const std::vector< Polygon > & context)
{
  Polygon corner_polygon;
  std::transform(context.cbegin(), context.cend(), std::back_inserter(corner_polygon.points), getFrameRectLeftLower{});
  Point left_lower = getFrameRect(corner_polygon).first;
  std::transform(context.cbegin(), context.cend(), corner_polygon.points.begin(), getFrameRectRightUpper{});
  Point right_upper = getFrameRect(corner_polygon).second;
  return std::make_pair(left_lower, right_upper);
}

bool erohin::hasRightAngles(const Polygon & polygon)
{
  if (polygon.points.size() < 3)
  {
    throw std::logic_error("Cannot find any angle");
  }
  auto predicate = isRightAngle{ *(polygon.points.cend() - 2), *(polygon.points.cend() - 1) };
  return std::count_if(polygon.points.cbegin(), polygon.points.cend(), predicate);
}

double erohin::getArea(const Polygon & polygon)
{
  const std::vector< Point > & vertex = polygon.points;
  auto area_functor = evaluateArea{ *vertex.cbegin(), *vertex.cbegin() };
  std::vector< double > part_area;
  std::transform(vertex.cbegin(), vertex.cend(), std::back_inserter(part_area), area_functor);
  return std::accumulate(part_area.cbegin(), part_area.cend(), 0.0);
}
