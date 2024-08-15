#include "filters.hpp"

#include <algorithm>

bool zagrivnyy::isOdd(const Polygon &p)
{
  return p.points.size() % 2;
}

bool zagrivnyy::isEven(const Polygon &p)
{
  return !isOdd(p);
}

bool zagrivnyy::isIntersects(const Polygon &p1, const Polygon &p2)
{
  auto p1_minmax = std::minmax_element(p1.points.cbegin(), p1.points.cend());
  auto p2_minmax = std::minmax_element(p2.points.cbegin(), p2.points.cend());

  return (*p1_minmax.second >= *p2_minmax.first && *p1_minmax.first <= *p2_minmax.second);
}

bool zagrivnyy::isVertexesCount(size_t count, const Polygon &p)
{
  return p.points.size() == count;
}

bool zagrivnyy::compareAreas(const Polygon &p1, const Polygon &p2)
{
  return getPolygonArea(p1) < getPolygonArea(p2);
}

bool zagrivnyy::compareVertexes(const Polygon &p1, const Polygon &p2)
{
  return p1.points.size() < p2.points.size();
}

double zagrivnyy::calcMeanArea(const Polygon &p, size_t polygons)
{
  return getPolygonArea(p) / polygons;
}
