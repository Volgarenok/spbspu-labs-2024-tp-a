#include "shapes.h"
#include "Delimiter.h"

#include <iterator>
#include <algorithm>
#include <limits>
#include <functional>
#include <numeric>
#include <cmath>

using namespace kazennov;

std::istream& kazennov::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  Point p;
  in >> Delimiter{ '(' } >> p.x >> Delimiter{ ';' } >> p.y >> Delimiter{ ')' };
  if (in)
  {
    point = p;
  }
  return in;
}

std::ostream& kazennov::operator<<(std::ostream& out, const Point& point)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << "(" << point.x << ";" << point.y << ")";
  return out;
}

std::istream& kazennov::operator>>(std::istream& in, Polygon& polygon)
{
std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  int n = 0;
  in >> n;
  if (n < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  Polygon temp;
  using input_it_t = std::istream_iterator< Point >;
  std::copy_n(input_it_t{in}, n, std::back_inserter(temp.points));
  if (in)
  {
    polygon = temp;
  }
  return in;
}

std::ostream& kazennov::operator<<(std::ostream& out, const Polygon& polygon)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  int n = 0;
  in >> n;
  if (n < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  Polygon temp;
  std::copy_n(std::istream_iterator< Point >{in}, n, std::back_inserter(temp.points));
  if (in)
  {
    polygon = temp;
  }
  return in;
}

double kazennov::PolygonArea(const Polygon& polygon)
{
  using namespace std::placeholders;
  auto areaCounter = std::bind(TriangleForArea{ polygon.points[1] }, _1, _2, polygon.points[0]);
  return std::accumulate(polygon.points.cbegin(), polygon.points.cend(), 0.0, areaCounter);
}
