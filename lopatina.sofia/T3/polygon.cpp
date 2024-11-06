#include "polygon.hpp"
#include <cstddef>
#include <iterator>
#include <algorithm>
#include <stream_guard.hpp>
#include <delimiter_formats.hpp>

std::istream & lopatina::operator>>(std::istream & in, Point & dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  Point point;
  in >> DelimiterIO{'('} >> point.x >> DelimiterIO{';'} >> point.y >> DelimiterIO{')'};
  if (in)
  {
    dest = point;
  }
  return in;
}

std::istream & lopatina::operator>>(std::istream & in, Polygon & dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  size_t count = 0;
  in >> count;
  if (count < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  std::vector< Point > points;
  points.reserve(count);
  std::copy_n(std::istream_iterator< Point >{in}, count, std::back_inserter(points));
  if (in)
  {
    dest.points = points;
  }
  return in;
}

bool lopatina::operator==(const Point & lhs, const Point & rhs)
{
  return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

bool lopatina::operator==(const Polygon & lhs, const Polygon & rhs)
{
  return lhs.points == rhs.points;
}
