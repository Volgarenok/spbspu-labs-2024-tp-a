#include "polygon.hpp"

std::istream& chernikova::operator>>(std::istream& in, chernikova::Point& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> chernikova::DelimiterI{'(' };
  in >> dest.x;
  in >> chernikova::DelimiterI{';' };
  in >> dest.y;
  in >> chernikova::DelimiterI{')' };
  return in;
}

std::istream& chernikova::operator>>(std::istream& in, chernikova::Polygon& dest)
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
  using iter = std::istream_iterator< chernikova::Point >;
  dest.points.clear();
  std::copy_n(iter(in), count, std::back_inserter(dest.points));
  if (dest.points.size() != count)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  return in;
}
