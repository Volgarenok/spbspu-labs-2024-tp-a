#include "filters.hpp"

#include <algorithm>

bool zagrivnyy::checkParity(const Polygon &p, const Parity &parity)
{
  return (p.points.size() % 2 != 0) == parity;
}

double zagrivnyy::addAreaIf(double area, const Polygon &p, bool condition)
{
  if (condition)
  {
    area += p.getArea();
  }
  return area;
}

bool zagrivnyy::isSamePolygon(const Polygon &p1, const Polygon &p2)
{
  return p1 == p2;
}

bool zagrivnyy::isIntersects(const Polygon &p1, const Polygon &p2)
{
  auto p1_minmax = std::minmax_element(p1.points.cbegin(), p1.points.cend());
  auto p2_minmax = std::minmax_element(p2.points.cbegin(), p2.points.cend());

  return (*p1_minmax.second >= *p2_minmax.first && *p1_minmax.first <= *p2_minmax.second);
}
