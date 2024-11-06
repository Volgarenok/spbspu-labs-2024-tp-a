#include "Polygon.hpp"
#include <cstddef>
#include <iterator>
#include <algorithm>
#include "StreamGuard.hpp"
#include "Delimiter.hpp"

std::istream & vorobieva::operator>>(std::istream & in, Point & data)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  using del = vorobieva::DelimiterChar;
  Point point;
  in >> DelimiterChar{ '(' } >> point.x >> DelimiterChar{ ';' } >> point.y >> DelimiterChar{ ')' };
  if (in)
  {
    data = point;
  }
  return in;
}

std::istream & vorobieva::operator>>(std::istream & in, Polygon & data)
{
  std::istream::sentry sentry(in);
  if (!sentry)
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
  std::copy_n(std::istream_iterator< Point > {in}, count, std::back_inserter(points));
  if (in)
  {
    data.points = points;
  }
  return in;
}

bool vorobieva::operator==(const Point & left, const Point & right)
{
  return (left.x == right.x) && (left.y == right.y);
}

bool vorobieva::operator==(const Polygon & left, const Polygon & right)
{
  return left.points == right.points;
}
