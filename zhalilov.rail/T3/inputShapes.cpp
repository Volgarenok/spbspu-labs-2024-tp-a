#include "inputShapes.hpp"

#include <algorithm>
#include <iterator>
#include <istream>
#include <set>

#include <inputData.hpp>

#include "geometry.hpp"

namespace zhalilov
{
  bool operator<(const Point &first, const Point &second)
  {
    if (first.x == second.x)
    {
      return first.y < second.y;
    }
    return first.x < second.x;
  }
}

std::istream &zhalilov::operator>>(std::istream &in, Polygon &polygon)
{
  std::istream::sentry s(in);
  if (!s)
  {
    return in;
  }
  size_t vertexes = 0;
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
  std::set < Point > uniquePoints(points.begin(), points.end());
  if (in && vertexes == uniquePoints.size())
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
