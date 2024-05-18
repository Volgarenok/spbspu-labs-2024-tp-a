#include "datastruct.hpp"
#include <iterator>
#include <Delimeter.hpp>

std::istream& kuznetsov::operator>>(std::istream& in, Point& point)
{
  using delchr = DelimeterChar;
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  int x = 0;
  int y = 0;
  in >> delchr{ '(' } >> x >> delchr{ ';' } >> y >> delchr{ ')' };
  if (in)
  {
    point = { x, y };
  }
  return in;
}

std::istream& kuznetsov::operator>>(std::istream& in, Polygon& polygon)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  size_t n = 0;
  in >> n;
  if (n < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  std::vector< Point > points;
  using input_it_t = std::istream_iterator< kuznetsov::Point >;
  std::copy_n(input_it_t{ in }, n, std::back_inserter(points));
  if (in && n == points.size())
  {
    polygon = { points };
  }
  return in;
}

