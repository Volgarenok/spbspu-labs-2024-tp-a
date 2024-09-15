#include "Polygon.hpp"
#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>
#include <delimiter.hpp>

std::istream& kozlova::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  in >> DelimiterCharIO{ '(' } >> point.x >> DelimiterCharIO{ ';' } >> point.y >> DelimiterCharIO{ ')' };
  return in;
}

bool kozlova::operator==(const Point& point1, const Point& point2)
{
  return point1.x == point2.x && point1.y == point2.y;
}

std::istream& kozlova::operator>>(std::istream& in, Polygon& polygon)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  std::size_t num = 0;
  in >> num;
  if (num < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  std::vector< Point > point;
  point.reserve(num);
  std::copy_n(std::istream_iterator< Point > { in }, num, std::back_inserter(point));

  if (in && point.size() == num)
  {
    polygon.points = std::move(point);
  }

  return in;
}

bool kozlova::operator==(const Polygon& polygon1, const Polygon& polygon2)
{
  return polygon1.points == polygon2.points;
}

struct calculatArea
{
  kozlova::Point point0;
  kozlova::Point changPoint;
  double operator()(const kozlova::Point& nextPoint)
  {
    double area = 0.5 * std::abs((nextPoint.x - point0.x) * (changPoint.y - point0.y) - (changPoint.x - point0.x) * (nextPoint.y - point0.y));
    changPoint = nextPoint;
    return area;
   }
};

double kozlova::getAreaPolygon(const Polygon& polygon)
{
  auto area_func = calculatArea{ polygon.points[0], polygon.points[0] };
  std::vector< double > summandArea(polygon.points.size());
  std::transform(polygon.points.cbegin(), polygon.points.cend(), std::back_inserter(summandArea), area_func);
  return std::accumulate(summandArea.cbegin(), summandArea.cend(), 0.0);
}

double kozlova::getAreaPolygons(const std::vector< Polygon >& polygons)
{
  std::vector< double > area(polygons.size());
  std::transform(polygons.cbegin(), polygons.cend(), std::back_inserter(area), getAreaPolygon);
  return std::accumulate(area.cbegin(), area.cend(), 0.0);
}
