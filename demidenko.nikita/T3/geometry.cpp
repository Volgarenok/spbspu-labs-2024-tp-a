#include "geometry.hpp"
#include <algorithm>
#include <cstddef>
#include <istream>
#include <iterator>
#include <vector>
#include <delimeter.hpp>
#include <streamGuard.hpp>

std::istream& demidenko::operator>>(std::istream& in, demidenko::Point& point)
{
  demidenko::StreamGuard guard(in);
  in >> std::noskipws;
  std::istream::sentry sentry(in);
  if (sentry)
  {
    using del = demidenko::DelimeterI;
    in >> del{ "(" } >> point.x >> del{ ";" } >> point.y >> del{ ")" };
  }
  return in;
}
std::ostream& demidenko::operator<<(std::ostream& out, const demidenko::Point& point)
{
  std::ostream::sentry sentry(out);
  if (sentry)
  {
    out << '(' << point.x << ';' << point.y << ')';
  }
  return out;
}
std::istream& demidenko::operator>>(std::istream& in, demidenko::Polygon& polygon)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  std::size_t size = 0;
  in >> size;
  if (size < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  polygon.points.clear();
  using InputIterator = std::istream_iterator< demidenko::Point >;
  std::copy_n(InputIterator{ in }, size, std::back_inserter(polygon.points));
  return in;
}
std::ostream& demidenko::operator<<(std::ostream& out, const demidenko::Polygon& polygon)
{
  std::ostream::sentry sentry(out);
  if (sentry)
  {
    out << polygon.points.size() << ' ';
    using OutputIterator = std::ostream_iterator< demidenko::Point >;
    std::copy(polygon.points.begin(), polygon.points.end(), OutputIterator{ out, " " });
  }
  return out;
}
std::istream& demidenko::readPolygons(std::istream& in, std::vector< Polygon >& polygons)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  using InputIterator = std::istream_iterator< demidenko::Polygon >;
  while (!in.eof())
  {
    if (in.fail())
    {
      in.clear();
    }
    std::copy(InputIterator{ in }, InputIterator{}, std::back_inserter(polygons));
  }
  return in;
}
