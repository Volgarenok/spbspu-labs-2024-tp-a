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
  std::vector< Point > temp(count);
  std::copy_n(
    std::istream_iterator< Point >(input),
    count,
    temp.begin()
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

namespace erohin
{
  bool isLessByX(const Point & lhs, const Point & rhs);
  bool isLessByY(const Point & lhs, const Point & rhs);
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

namespace erohin
{
  struct getFrameRectLeftLower
  {
    Point operator()(const Polygon & polygon);
  };

  struct getFrameRectRightUpper
  {
    Point operator()(const Polygon & polygon);
  };
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

namespace erohin
{
  struct isRightAngle
  {
    Point prev;
    Point center;
    bool operator()(const Point & point);
  };
}

bool erohin::hasRightAngles(const Polygon & polygon)
{
  if (polygon.points.size() < 3)
  {
    throw std::logic_error("Cannot find any angle");
  }
  auto predicate = isRightAngle{ *(polygon.points.cend() - 2), *(polygon.points.cend() - 1) };
  return std::any_of(polygon.points.cbegin(), polygon.points.cend(), predicate);
}

namespace erohin
{
  struct evaluateArea
  {
    Point start;
    Point prev;
    double operator()(const Point & point)
    {
      double area = std::abs((point.x - start.x) * (prev.y - start.y) - (prev.x - start.x) * (point.y - start.y)) / 2.0;
      prev = point;
      return area;
    }
  };
}

double erohin::getArea(const Polygon & polygon)
{
  const std::vector< Point > & vertex = polygon.points;
  auto area_functor = evaluateArea{ *vertex.cbegin(), *vertex.cbegin() };
  std::vector< double > part_area(vertex.size());
  std::transform(vertex.cbegin(), vertex.cend(), part_area.begin(), area_functor);
  return std::accumulate(part_area.cbegin(), part_area.cend(), 0.0);
}

double erohin::getArea(const std::vector< Polygon > & context)
{
  std::vector< double > area(context.size());
  double (*area_counter)(const Polygon &) = getArea;
  std::transform(context.cbegin(), context.cend(), area.begin(), area_counter);
  return std::accumulate(area.cbegin(), area.cend(), 0.0);
}

bool erohin::isLessByX(const Point & lhs, const Point & rhs)
{
  return (lhs.x < rhs.x);
}

bool erohin::isLessByY(const Point & lhs, const Point & rhs)
{
  return (lhs.y < rhs.y);
}

erohin::Point erohin::getFrameRectLeftLower::operator()(const Polygon & polygon)
{
  return getFrameRect(polygon).first;
}

erohin::Point erohin::getFrameRectRightUpper::operator()(const Polygon & polygon)
{
  return getFrameRect(polygon).second;
}

bool erohin::isRightAngle::operator()(const Point & point)
{
  size_t scalar_miltiply = std::abs((point.x - center.x) * (prev.x - center.x) + (point.y - center.y) * (prev.y - center.y));
  prev = center;
  center = point;
  return !scalar_miltiply;
}
