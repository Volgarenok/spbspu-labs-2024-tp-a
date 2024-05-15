#include "Polygon.hpp"
#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>
#include <delimiter.hpp>

std::istream& kozlova::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
      return in;
  }

  in >> DelimiterCharIO{ '(' } >> point.x >> DelimiterCharIO{ ';' } >> point.y >> DelimiterCharIO{ ')' };
  return in;
}

std::istream& kozlova::operator>>(std::istream& in, Polygon& polygon)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
      return in;
  }

  std::size_t num = 0;
  in >> num;
  if (num < 3)
  {
      in.setstate(std::ios::failbit);
      return in;
  }

  std::vector< Point > point;
  point.reserve(num);
  std::copy_n(std::istream_iterator< Point > { in }, num, std::back_inserter(point));

  if (in && point.size() == num)
  {
      polygon.points = std::move(point);
  }

  return in;
}
