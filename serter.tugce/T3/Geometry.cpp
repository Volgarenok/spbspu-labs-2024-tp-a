#include "Geometry.hpp"

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
  using iter = std::istream_iterator< Point >;
  dest.points.clear();
  std::copy_n(iter(in), count, std::back_inserter(dest.points));
  if (dest.points.size() != count)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  return in;
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

