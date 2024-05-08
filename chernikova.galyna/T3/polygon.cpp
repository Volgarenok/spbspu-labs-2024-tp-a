#include "polygon.hpp"

std::istream& chernikova::operator>>(std::istream& in, chernikova::Point& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> chernikova::DelimiterI{'(' };
  in >> dest.x;
  in >> chernikova::DelimiterI{';' };
  in >> dest.y;
  in >> chernikova::DelimiterI{')' };
  return in;
}

std::istream& chernikova::operator>>(std::istream& in, chernikova::Polygon& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  size_t count = 0;
  in >> count;
  if (count < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  using iter = std::istream_iterator< chernikova::Point >;
  dest.points.clear();
  std::copy_n(iter(in), count, std::back_inserter(dest.points));
  if (dest.points.size() != count)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  return in;
}

bool chernikova::isEven(const chernikova::Polygon& polygon)
{
  return polygon.points.size() % 2 == 0;
}

bool chernikova::isOdd(const chernikova::Polygon& polygon)
{
  return !isEven(polygon);
}

double chernikova::calcArea(const chernikova::Point& left, const chernikova::Point& right)
{
  return 0.5 * (left.x * right.y - right.x * left.y);
}

double chernikova::getArea(const chernikova::Polygon& polygon)
{
  double res = 0.0;
  for (size_t i = 0; i < polygon.points.size() - 1; ++i)
  {
    res += chernikova::calcArea(polygon.points[i], polygon.points[i + 1]);
  }
  res += chernikova::calcArea(polygon.points.back(), polygon.points.front());
  return std::abs(res);
}

double chernikova::sumArea(double cur, const chernikova::Polygon& polygon)
{
  return cur + chernikova::getArea(polygon);
}

void chernikova::getAreaEven(const std::vector< Polygon >& polygons, std::ostream& out)
{
  std::vector< Polygon > even_polygons;
  std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(even_polygons), chernikova::isEven);
  StreamGuard streamGuard(out);
  out << std::fixed << std::setprecision(1);
  out << std::accumulate(even_polygons.begin(), even_polygons.end(), 0.0, chernikova::sumArea) << "\n";
}

void chernikova::getAreaOdd(const std::vector< Polygon >& polygons, std::ostream& out)
{
  std::vector< Polygon > odd_polygons;
  std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(odd_polygons), chernikova::isOdd);
  StreamGuard streamGuard(out);
  out << std::fixed << std::setprecision(1);
  out << std::accumulate(odd_polygons.begin(), odd_polygons.end(), 0.0, chernikova::sumArea) << "\n";
}
