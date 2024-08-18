#include "helpers.hpp"

#include <numeric>
#include <algorithm>

bool demin::odd(const Polygon &p)
{
  return p.points.size() % 2;
}

bool demin::even(const Polygon &p)
{
  return !odd(p);
}

bool demin::checkVertexes(size_t count, const Polygon &p)
{
  return p.points.size() == count;
}

bool demin::compareAreas(const Polygon &p1, const Polygon &p2)
{
  return getArea(p1) < getArea(p2);
}

bool demin::compareVertexes(const Polygon &p1, const Polygon &p2)
{
  return p1.points.size() < p2.points.size();
}

double demin::getArea(const Polygon& points)
{
  using namespace std::placeholders;
  auto res = std::bind(AccumulateArea{points.points[1]}, _1, _2, points.points[0]);
  return std::accumulate(points.points.cbegin(), points.points.cend(), 0.0, res);
}

bool demin::isRight(const demin::Polygon& polygon)
{
  using namespace std::placeholders;
  Point p1 = polygon.points[polygon.points.size() - 1];
  Point p2 = polygon.points[polygon.points.size() - 2];
  auto countAngleFilter = std::bind(countAngle, std::ref(p1), std::ref(p2), _1 );

  return std::find_if(polygon.points.cbegin(), polygon.points.cend(), countAngleFilter) != polygon.points.cend();
}

bool demin::countAngle(Point &p1, Point &p2, const Point &p3)
{
  Point side1 = { p2.x - p1.x, p2.y - p1.y };
  Point side2 = { p3.x - p1.x, p3.y - p1.y };

  p1 = p2;
  p2 = p3;

  return side1.x * side2.x + side1.y * side2.y == 0;
}