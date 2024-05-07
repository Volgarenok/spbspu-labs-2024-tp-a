#include "inputShapes.hpp"

#include <algorithm>
#include <iterator>
#include <istream>

#include <inputData.hpp>

#include "geometry.hpp"

std::istream &zhalilov::operator>>(std::istream &in, Polygon &polygon)
{
  std::istream::sentry s(int);
  if (!s)
  {
    return in;
  }
  size_t numOfPoly{};
  in >> numOfPoly;
  std::vector < Point > points{};
  std::copy_n(std::istream_iterator < Point >(in),
              numOfPoly,
              std::back_inserter(points));
  polygon.points = points;
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
