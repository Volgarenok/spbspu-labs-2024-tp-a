#include "geometry.hpp"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <functional>
#include <iterator>
#include <limits>
#include <numeric>
#include <utility>
#include <vector>
#include <delimeter.hpp>
#include <streamGuard.hpp>

std::istream& demidenko::operator>>(std::istream& in, Point& point)
{
  StreamGuard guard(in);
  std::istream::sentry sentry(in);
  in >> std::noskipws;
  if (sentry)
  {
    using del = DelimeterI;
    in >> del{ "(" } >> point.x >> del{ ";" } >> point.y >> del{ ")" };
  }
  return in;
}
std::ostream& demidenko::operator<<(std::ostream& out, const Point& point)
{
  std::ostream::sentry sentry(out);
  if (sentry)
  {
    out << '(' << point.x << ';' << point.y << ')';
  }
  return out;
}
std::istream& demidenko::operator>>(std::istream& in, Polygon& polygon)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  size_t size = 0;
  in >> size;
  if (size < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  polygon.points.clear();
  using InputIterator = std::istream_iterator< Point >;
  std::copy_n(InputIterator{ in }, size, std::back_inserter(polygon.points));
  return in;
}
std::ostream& demidenko::operator<<(std::ostream& out, const Polygon& polygon)
{
  std::ostream::sentry sentry(out);
  if (sentry)
  {
    out << polygon.points.size() << ' ';
    using OutputIterator = std::ostream_iterator< Point >;
    std::copy(polygon.points.begin(), polygon.points.end(), OutputIterator{ out, " " });
  }
  return out;
}
double demidenko::getPolygonArea(const Polygon& polygon)
{
  Point init = polygon.points[0];
  std::vector< std::pair< Point, Point > > bases(polygon.points.size() - 2, std::make_pair(Point{}, Point{}));
  auto makePointPair = std::make_pair< const Point&, const Point& >;
  std::transform(
    polygon.points.begin() + 2,
    polygon.points.end(),
    polygon.points.begin() + 1,
    bases.begin(),
    makePointPair
  );
  using namespace std::placeholders;
  return std::accumulate(
    bases.begin(),
    bases.end(),
    0.0,
    std::bind(std::plus< double >{}, _1, std::bind(getTriangleArea, init, _2))
  );
}
bool demidenko::isRightPolygon(const Polygon& polygon)
{
  std::vector< Point > rotated(polygon.points.size(), Point{});
  std::rotate_copy(polygon.points.begin(), polygon.points.begin() + 2, polygon.points.end(), rotated.begin());
  std::vector< std::pair< Point, Point > > bases(polygon.points.size(), std::make_pair(Point{}, Point{}));
  auto makePointPair = std::make_pair< const Point&, const Point& >;
  std::transform(polygon.points.begin(), polygon.points.end(), rotated.begin(), bases.begin(), makePointPair);
  std::rotate_copy(polygon.points.begin(), polygon.points.begin() + 1, polygon.points.end(), rotated.begin());
  using namespace std::placeholders;
  return !std::equal(
    rotated.begin(),
    rotated.end(),
    bases.begin(),
    std::bind(std::logical_not<>(), std::bind(isRightTriangle, _1, _2))
  );
}
double demidenko::getTriangleArea(const Point& top, const std::pair< const Point&, const Point& > base)
{
  double a = getDistance(top, base.first);
  double b = getDistance(base.first, base.second);
  double c = getDistance(base.second, top);
  double p = (a + b + c) / 2;
  return std::sqrt(p * (p - a) * (p - b) * (p - c));
}
bool demidenko::isRightTriangle(const Point& top, std::pair< const Point&, const Point& > base)
{
  double a = getDistance(top, base.first);
  double b = getDistance(top, base.second);
  double c = getDistance(base.first, base.second);
  return std::abs(std::hypot(a, b) - c) < 0.00001;
}
double demidenko::getDistance(const Point& first, const Point& second)
{
  return std::hypot(first.x - second.x, first.y - second.y);
}
bool demidenko::isPointEqual(const Point& first, const Point& second)
{
  return first.x == second.x && first.y == second.y;
}
bool demidenko::isPolygonEqual(const Polygon& first, const Polygon& second)
{
  return std::equal(first.points.begin(), first.points.end(), second.points.begin(), isPointEqual);
}
