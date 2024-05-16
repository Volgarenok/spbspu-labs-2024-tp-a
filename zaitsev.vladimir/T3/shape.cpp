#include "shape.hpp"
#include <algorithm>
#include <iterator>
#include <limits>
#include <delimiter.hpp>

zaitsev::Point zaitsev::operator+(Point pt1, Point pt2)
{
  return { pt1.x + pt2.x, pt1.y + pt2.y };
}

zaitsev::Point zaitsev::operator-(Point pt1, Point pt2)
{
  return { pt1.x - pt2.x, pt1.y - pt2.y };
}

std::istream& zaitsev::operator>>(std::istream& in, Point& val)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> Delimiter{ "(" } >> val.x >> Delimiter{ ";" } >> val.y >> Delimiter{ ")" };
}

std::istream& zaitsev::operator>>(std::istream& in, Polygon& val)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  size_t sz = 0;
  in >> sz;
  if (sz < 3)
  {
    in.setstate(std::ios::failbit);
  }
  val.points.clear();
  std::copy_n(std::istream_iterator< Point >(in), sz, std::back_inserter(val.points));

  return in;
}
