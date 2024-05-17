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
  Point new_pt;
  in >> Delimiter{ "(" } >> new_pt.x >> Delimiter{ ";" } >> new_pt.y >> Delimiter{ ")" };
  if (in)
  {
    val = new_pt;
  }
  return in;
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
    return in;
  }
  std::vector< Point > new_pts;
  new_pts.reserve(sz);
  std::copy_n(std::istream_iterator< Point >(in), sz, std::back_inserter(new_pts));
  if (in)
  {
    val.points = std::move(new_pts);
  }
  return in;
}
