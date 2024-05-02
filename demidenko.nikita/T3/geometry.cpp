#include "geometry.hpp"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <functional>
#include <iterator>
#include <limits>
#include <numeric>
#include <vector>
#include <delimeter.hpp>
#include <streamGuard.hpp>

std::istream& demidenko::operator>>(std::istream& in, demidenko::Point& point)
{
  demidenko::StreamGuard guard(in);
  std::istream::sentry sentry(in);
  in >> std::noskipws;
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
    std::copy(InputIterator{ in }, InputIterator{}, std::back_inserter(polygons));
    if (in.fail())
    {
      in.clear();
      in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return in;
}
double demidenko::polygonArea(const Polygon& polygon)
{
  Point init = polygon.points[0];
  std::vector< std::pair< Point, Point > > bases;
  using namespace std::placeholders;
  std::transform(
    polygon.points.begin() + 2,
    polygon.points.end(),
    polygon.points.begin() + 1,
    std::back_inserter(bases),
    std::make_pair< const Point&, const Point& > // Угловые кавычки сводят форматер с ума
  );
  using namespace std::placeholders;
  return std::accumulate(
    bases.begin(),
    bases.end(),
    0.0,
    std::bind(std::plus< double >{}, _1, std::bind(triangleArea, init, _2))
  );
}
bool demidenko::isRightPolygon(const Polygon& polygon)
{
  std::vector< Point > rotated;
  std::rotate_copy(
    polygon.points.begin(),
    polygon.points.begin() + 1,
    polygon.points.end(),
    std::back_inserter(rotated)
  );
  std::vector< std::pair< Point, Point > > bases;
  std::transform(
    polygon.points.begin(),
    polygon.points.end(),
    rotated.begin(),
    std::back_inserter(bases),
    std::make_pair< const Point&, const Point& > // Угловые кавычки сводят форматер с ума
  );
  std::rotate(rotated.begin(), rotated.begin() + 1, rotated.end());
  using namespace std::placeholders;
  return !std::equal(
    rotated.begin(),
    rotated.end(),
    bases.begin(),
    std::bind(std::logical_not<>(), std::bind(isRightTriangle, _1, _2))
  );
}
double demidenko::triangleArea(const Point& top, const std::pair< const Point&, const Point& > base)
{
  double a = distance(top, base.first);
  double b = distance(base.first, base.second);
  double c = distance(base.second, top);
  double p = (a + b + c) / 2;
  return std::sqrt(p * (p - a) * (p - b) * (p - c));
}
bool demidenko::isRightTriangle(const Point& top, std::pair< const Point&, const Point& > base)
{
  double a = distance(top, base.first);
  double b = distance(base.first, base.second);
  double c = distance(base.second, top);
  return std::abs(std::hypot(a, b) - c) < 0.00001;
}
double demidenko::distance(const Point& first, const Point& second)
{
  return std::hypot(first.x - second.x, first.y - second.y);
}
bool demidenko::Point::operator==(const Point& other) const
{
  return x == other.x && y == other.y;
}
