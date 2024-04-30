#include "datastruct.hpp"
#include "delimeter.hpp"
#include <iterator>
#include <algorithm>

std::istream& kuznetsov::operator>>(std::istream& in, Point& point)
{
  using delchr = DelimeterChar;
  std::istream::sentry guard(in);
  if (guard)
  {
    int x = 0;
    int y = 0;
    in >> delchr{ '(' } >> x >> delchr{ ';' } >> y >> delchr{ ')' };
    if (in)
    {
      point = { x, y };
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
  }
  return in;
}

std::istream& kuznetsov::operator>>(std::istream& in, Polygon& polygon)
{
  std::istream::sentry guard(in);
  if (guard)
  {
    size_t n = 0;
    in >> n;
    std::vector< Point > points;
    using input_it_t = std::istream_iterator< kuznetsov::Point >;
    std::copy_n(input_it_t{ in }, n, std::back_inserter(points));
    if (in)
    {
      polygon = { points };
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
  }
  return in;
}
