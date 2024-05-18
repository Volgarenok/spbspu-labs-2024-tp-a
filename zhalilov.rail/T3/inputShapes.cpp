#include "inputShapes.hpp"

#include <algorithm>
#include <iterator>
#include <istream>

#include <inputData.hpp>
#include <set>

#include "geometry.hpp"
#include "pointCompare.hpp"

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

  if (in && vertexes == points.size())
  {
    std::set < Point > toCheckDuplicates(points.cbegin(), points.cend());
    if (toCheckDuplicates.size() == points.size())
    {
      polygon.points = points;
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
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
