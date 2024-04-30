#include "Polygon.hpp"
#include <Delimeter.hpp>

#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>

std::istream & erfurt::operator>>(std::istream & in, Point & point)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  using del = Delimeter;

  int x = 0;
  int y = 0;

  in >> del{"("} >> x >> del{";"} >> y >> del{")"};

  if (in)
  {
    point = Point{x, y};
  }
  return in;
}

std::istream & erfurt::operator>>(std::istream & in, Polygon & poly)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  std::size_t n = 0;

  in >> n;

  if (n < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  std::vector <Point> points;
  points.reserve(n);
  for (std::size_t i = 0; i < n; ++i)
  {
    Point point{0, 0};
    if (in >> point)
    {
      points.push_back(point);
    }
  }
  if (in)
  {
    poly.points = points;
  }
  return in;
}

double erfurt::AccumulatePolygonArea::operator()(double area, const Point & p1, const Point & p2)
{
  area += 0.5 * std::abs((p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y));
  p0 = p1;
  return area;
}

double erfurt::Polygon::getArea() const
{
  using namespace std::placeholders;
  auto area = std::bind(AccumulatePolygonArea{ points[0] }, _1, _2, points[0]);
  return std::accumulate(points.cbegin(), points.cend(), 0.0, area);
}

bool erfurt::isPointConsist(const Point & point, const Polygon & poly)
{
  bool isIn = std::find(poly.points.cbegin(), poly.points.cend(), point) != poly.points.cend();
  Point reversePoint({point.y, point.x});
  return isIn || std::find(poly.points.cbegin(), poly.points.cend(), reversePoint) != poly.points.cend();
}

bool erfurt::Point::operator==(const Point & other) const
{
  return (x == other.x && y == other.y);
}

bool erfurt::Polygon::operator==(const Polygon & poly) const
{
  return points == poly.points;
}
