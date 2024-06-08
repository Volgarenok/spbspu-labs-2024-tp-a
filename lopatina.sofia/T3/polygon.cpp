#include "polygon.hpp"
#include <cstddef>
#include <iterator>
#include "stream_guard.hpp"
#include "delimiter_formats.hpp"

std::istream & lopatina::operator>>(std::istream & in, Polygon & dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  Polygon polygon;
  int count = 0;
  in >> count;
  for (size_t i = 0; i < count; ++i)
  {
    Point point;
    in >> DelimiterIO{'('} >> point.x >> DelimiterIO{';'} >> point.y >> DelimiterIO{')'};
    if (in)
    {
      polygon.points.push_back(point);
    }
  }
  if (in)
  {
    dest = polygon;
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
