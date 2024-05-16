#include "inputShapes.hpp"

#include <algorithm>
#include <iterator>
#include <istream>

#include <inputData.hpp>

#include "geometry.hpp"

std::istream &zhalilov::operator>>(std::istream &in, Polygon &polygon)
{
  std::istream::sentry s(in);
  if (!s)
  {
    return in;
  }
  size_t vertexes{};
  in >> vertexes;
  if (vertexes < 3)
  {
    in.setstate(std::ios::failbit);
  }
  std::vector < Point > points{};
  std::copy_n(
    std::istream_iterator < Point >(in),
    vertexes,
    std::back_inserter(points)
  );
  if (in && vertexes == points.size())
  {
    polygon.points = points;
  }
  return in;
}

std::istream &zhalilov::operator>>(std::istream &in, Point &point)
{
  std::istream::sentry s(in);
  if (!s)
  {
    return in;
  }

  in >> DelimiterI{ '(' } >> point.x >> DelimiterI{ ';' } >> point.y >> DelimiterI{ ')' };
  return in;
}
