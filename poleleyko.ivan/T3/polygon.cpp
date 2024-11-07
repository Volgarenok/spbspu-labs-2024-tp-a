#include "polygon.hpp"
#include <vector>
#include <algorithm>
#include <iterator>
#include "delimiter.hpp"

std::istream & poleleyko::operator>>(std::istream & in, Point & point)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  int x = 0;
  int y = 0;
  in >> DelimiterIO{ '(' };
  in >> x >> DelimiterIO{ ';' } >> y;
  in >> DelimiterIO{ ')' };
  if (!in)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  point.x = x;
  point.y = y;
  return in;
}

std::istream & poleleyko::operator>>(std::istream & in, Polygon & polygon)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  size_t count = 0;
  in >> count;
  if (!in || count < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  std::vector< Point > points;
  points.reserve(count);
  std::copy_n(std::istream_iterator< Point >{ in }, count - 1, std::back_inserter(points));
  if (in.peek() != '\n')
  {
    std::copy_n(std::istream_iterator< Point >{ in }, 1, std::back_inserter(points));
  }
  if (!in || points.size() != count || in.peek() != '\n')
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  polygon.points = points;
  return in;
}