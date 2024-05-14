#include "polygon.hpp"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <delimiter.hpp>
#include "predicates.hpp"

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

std::pair< erohin::Point, erohin::Point > erohin::Polygon::getFrameRect() const
{
  auto x_range = std::minmax_element(points.cbegin(), points.cend(), isXCoordinateLess);
  auto y_range = std::minmax_element(points.cbegin(), points.cend(), isYCoordinateLess);
  Point left_lower_corner{ x_range.first->x, y_range.first->y };
  Point right_upper_corner{ x_range.second->x, y_range.second->y };
  return std::make_pair(left_lower_corner, right_upper_corner);
}

bool erohin::Polygon::isRightAngle(size_t vertex_index) const
{
  size_t size = points.size();
  Point cur = points[vertex_index];
  Poinr prev = points[vertex_index ? size - 1 : vertex_index - 1];
  Point next = points[(vertex_index + 1) % size];
  int scalar_multiply = (cur.x - prev.x) * (cur.x - next.x) + (cur.y - prev.y) * (cur.y - next.y);
  return !scalar_multiply;
}

bool erohin::Polygon::countRightAngles() const
{
  return find_if(points.cbegin(), points.cend(), Polygon::isRightAngle) != point.cend();
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
  output << polygon.points.size() << " ";
  std::copy(
    polygon.points.cbegin(),
    polygon.points.cend(),
    std::ostream_iterator< Point >(output, " ")
  );
  return output;
}
