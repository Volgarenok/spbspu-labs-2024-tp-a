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
