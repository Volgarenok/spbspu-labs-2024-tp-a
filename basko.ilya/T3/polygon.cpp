#include "polygon.hpp"
#include <delimiters.hpp>
#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>

std::istream& basko::operator>>(std::istream& in, Point& point)
{
  using delChar = DelimiterChar;
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  Point temp = { 0, 0 };
  in >> delChar{ '(' } >> temp.x >> delChar{ ';' } >> temp.y >> delChar{ ')' };
  if (in)
  {
    point = temp;
  }
  return in;
}

bool basko::operator==(const Point& lhs, const Point& rhs)
{
  return ((lhs.x == rhs.x) && (lhs.y == rhs.y));
}

double basko::getPolygonArea(const Polygon& polygon)
{
  using namespace std::placeholders;
  auto accumulateArea = std::bind(AreaPolygon{ polygon.points[1] }, _1, _2, polygon.points[0]);
  return std::accumulate(polygon.points.cbegin(), polygon.points.cend(), 0.0, accumulateArea);
}
