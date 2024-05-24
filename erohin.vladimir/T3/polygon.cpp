#include "polygon.hpp"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <functional>
#include <numeric>
#include "point.hpp"
#include "delimiter.hpp"

std::istream & erohin::operator>>(std::istream & input, Polygon & polygon)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  size_t count = 0;
  input >> count;
  if (count < 3)
  {
    input.setstate(std::ios::failbit);
    return input;
  }
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
  if (polygon.points.empty())
  {
    output << 0;
  }
  else
  {
    output << polygon.points.size() << " ";
    std::copy(
      polygon.points.cbegin(),
      std::prev(polygon.points.cend()),
      std::ostream_iterator< Point >(output, " ")
    );
    output << *std::prev(polygon.points.cend());
  }
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
  std::transform(context.cbegin(), context.cend(), std::back_inserter(corner_polygon.points), detail::getFrameRectLeftLower{});
  Point left_lower = getFrameRect(corner_polygon).first;
  std::transform(context.cbegin(), context.cend(), corner_polygon.points.begin(), detail::getFrameRectRightUpper{});
  Point right_upper = getFrameRect(corner_polygon).second;
  return std::make_pair(left_lower, right_upper);
}

bool erohin::isVertexNumberEven(const Polygon & polygon)
{
  return (polygon.points.size() % 2 == 0);
}

bool erohin::isVertexNumberOdd(const Polygon & polygon)
{
  return !isVertexNumberEven(polygon);
}

bool erohin::isVertexNumber(const Polygon & polygon, size_t number)
{
  return (polygon.points.size() == number);
}

bool erohin::isLessByArea(const Polygon & lhs, const Polygon & rhs)
{
  return (getArea(lhs) < getArea(rhs));
}

bool erohin::isLessBySize(const Polygon & lhs, const Polygon & rhs)
{
  return (lhs.points.size() < rhs.points.size());
}

bool erohin::hasRightAngles(const Polygon & polygon)
{
  if (polygon.points.size() < 3)
  {
    throw std::logic_error("Cannot find any angle");
  }
  auto predicate = detail::isRightAngle{ *(polygon.points.cend() - 2), *(polygon.points.cend() - 1) };
  return std::any_of(polygon.points.cbegin(), polygon.points.cend(), predicate);
}

double erohin::getArea(const Polygon & polygon)
{
  const std::vector< Point > & vertex = polygon.points;
  auto area_functor = detail::evaluateArea{ *vertex.cbegin(), *vertex.cbegin() };
  std::vector< double > part_area;
  std::transform(vertex.cbegin(), vertex.cend(), std::back_inserter(part_area), area_functor);
  return std::accumulate(part_area.cbegin(), part_area.cend(), 0.0);
}

double erohin::getArea(const std::vector< Polygon > & context)
{
  std::vector< double > area;
  double (*area_counter)(const Polygon &) = getArea;
  std::transform(context.cbegin(), context.cend(), std::back_inserter(area), area_counter);
  return std::accumulate(area.cbegin(), area.cend(), 0.0);
}

double erohin::detail::evaluateArea::operator()(const Point & point)
{
  double area = std::abs((point.x - start.x) * (prev.y - start.y) - (prev.x - start.x) * (point.y - start.y)) / 2.0;
  prev = point;
  return area;
}

bool erohin::detail::isRightAngle::operator()(const Point & point)
{
  size_t scalar_miltiply = std::abs((point.x - center.x) * (prev.x - center.x) + (point.y - center.y) * (prev.y - center.y));
  prev = center;
  center = point;
  return !scalar_miltiply;
}

erohin::Point erohin::detail::getFrameRectLeftLower::operator()(const Polygon & polygon)
{
  return getFrameRect(polygon).first;
}

erohin::Point erohin::detail::getFrameRectRightUpper::operator()(const Polygon & polygon)
{
  return getFrameRect(polygon).second;
}
