#include "Geometry.h"

#include <algorithm>
#include <iterator>

#include "ReadIO.h"

static size_t index = 0;

std::istream& serter::operator>>(std::istream& in, Polygon& dest)
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
  using iter = std::istream_iterator< serter::Point >;
  dest.points.clear();
  std::copy_n(iter(in), count, std::back_inserter(dest.points));
  if (dest.points.size() != count)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  return in;
}

bool serter::operator==(const Point& lhs, const Point& rhs)
{
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

std::istream& serter::operator>>(std::istream& in, Point& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> DelimiterIO{ '(' };
  in >> dest.x;
  in >> DelimiterIO{ ';' };
  in >> dest.y;
  in >> DelimiterIO{ ')' };
  return in;
}
