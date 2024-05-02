#include "shapes.hpp"
#include <istream>
#include <iterator>
#include <algorithm>
#include <Delimiter.hpp>

std::istream& artemev::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  using delChar = artemev::DelimiterCharI;
  int x, y;
  in >> delChar({'('}) >> x >> delChar({';'}) >> y >> delChar({')'});
  if (in)
  {
    point.x = x;
    point.y = y;
  }
  return in;
}

std::istream& artemev::operator>>(std::istream& in, Polygon& polygon)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  int countTop;
  in >> countTop;
  if (countTop < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  std::vector< Point > points;
  std::copy_n(std::istream_iterator< Point >{ in }, countTop, std::back_inserter(points));

  if (in)
  {
    polygon.points = std::move(points);
  }

  return in;
}