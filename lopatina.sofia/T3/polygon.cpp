#include "polygon.hpp"
#include <cstddef>
#include <iterator>
#include <algorithm>
#include "stream_guard.hpp"
#include "delimiter_formats.hpp"

std::istream & lopatina::operator>>(std::istream & in, Point & dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  Point point;
  in >> DelimiterIO{'('} >> point.x >> DelimiterIO{';'} >> point.y >> DelimiterIO{')'};
  if (in)
  {
    dest = point;
  }
  return in;
}

std::istream & lopatina::operator>>(std::istream & in, Polygon & dest)
{
  std::istream::sentry guard(in);
  if (!guard)
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
  std::vector<Point> points;
  points.reserve(count);
  std::copy_n(std::istream_iterator< Point > (in), count, std::back_inserter(points));
  if (in)
  {
    dest.points = points;
  }
  return in;
}

std::ostream & lopatina::operator<<(std::ostream & out, const Polygon & data)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  StreamGuard fmtguard(out);
  for (auto iter = data.points.begin(); iter != data.points.end(); ++iter)
  {
    out << "(" << (*iter).x << ";" << (*iter).y << ") ";
  }
  return out;
}
