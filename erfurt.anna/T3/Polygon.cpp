#include "Polygon.hpp"
#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>
#include <Delimeter.hpp>

namespace erfurt
{
  struct AccumulateArea
  {
    Point p0;
    Point p2;
    double operator()(const Point & point)
    {
      double area = std::abs((point.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (point.y - p0.y)) / 2.0;
      p2 = point;
      return area;
    }
  };
}

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

  in >> del{ "(" } >> x >> del{ ";" } >> y >> del{ ")" };

  if (in)
  {
    point = Point{ x , y };
  }
  return in;
}

bool erfurt::operator==(const Point & point1, const Point & point2)
{
  return (point1.x == point2.x && point1.y == point2.y);
}

std::istream & erfurt::operator>>(std::istream & in, Polygon & poly)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  size_t n = 0;

  in >> n;

  if (n < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  std::vector <Point> points;
  points.reserve(n);
  for (size_t i = 0; i < n; ++i)
  {
    Point point{ 0, 0 };
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

double erfurt::getArea(const Polygon & polygon)
{
  const std::vector< Point> & vertex = polygon.points;
  auto area_func = AccumulateArea{ *vertex.cbegin(), *vertex.cbegin() };
  std::vector< double > part_area(vertex.size());
  std::transform(vertex.cbegin(), vertex.cend(), std::back_inserter(part_area), area_func);
  return std::accumulate(part_area.cbegin(), part_area.cend(), 0.0);
}

double erfurt::getAreaPolygons(const std::vector< Polygon > & poly)
{
  std::vector< double > area(poly.size());
  double (*area_count)(const Polygon&) = getArea;
  std::transform(poly.cbegin(), poly.cend(), std::back_inserter(area), area_count);
  return std::accumulate(area.cbegin(), area.cend(), 0.0);
}

bool erfurt::isPointIn(const Point & point, const Polygon & poly)
{
  bool isIn = std::find(poly.points.cbegin(), poly.points.cend(), point) != poly.points.cend();
  Point point2({ point.y, point.x });
  return isIn || std::find(poly.points.cbegin(), poly.points.cend(), point2) != poly.points.cend();
}

bool erfurt::isEqual(const Polygon & p1, const Polygon & p2)
{
  if (p1.points.size() != p2.points.size())
  {
    return false;
  }
  return std::equal(p1.points.begin(), p1.points.end(), p2.points.begin());
}
