#include "predicates.hpp"
#include <algorithm>

bool novikov::hasEvenVertexesCount(const Polygon& rhs)
{
  return rhs.points.size() % 2 == 0;
}

bool novikov::hasOddVertexesCount(const Polygon& rhs)
{
  return !hasEvenVertexesCount(rhs);
}

bool novikov::hasVertexesCount(const Polygon& rhs, std::size_t num)
{
  return rhs.points.size() == num;
}

bool novikov::compareAreas(const Polygon& lhs, const Polygon& rhs)
{
  return getArea(lhs) < getArea(rhs);
}

bool novikov::compareVertexes(const Polygon& lhs, const Polygon& rhs)
{
  return lhs.points.size() < rhs.points.size();
}

bool novikov::comparePointsX(const Point& lhs, const Point& rhs)
{
  return lhs.x < rhs.x;
}

bool novikov::comparePointsY(const Point& lhs, const Point& rhs)
{
  return lhs.y < rhs.y;
}

bool novikov::comparePolygonsMinX(const Polygon& lhs, const Polygon& rhs)
{
  auto lhs_min = std::min_element(lhs.points.cbegin(), lhs.points.cend(), comparePointsX);
  auto rhs_min = std::min_element(rhs.points.cbegin(), rhs.points.cend(), comparePointsY);

  return comparePointsX(*lhs_min, *rhs_min);
}

bool novikov::comparePolygonsMinY(const Polygon& lhs, const Polygon& rhs)
{
  auto lhs_min = std::min_element(lhs.points.cbegin(), lhs.points.cend(), comparePointsY);
  auto rhs_min = std::min_element(rhs.points.cbegin(), rhs.points.cend(), comparePointsY);

  return comparePointsY(*lhs_min, *rhs_min);
}

bool novikov::comparePolygonsMaxX(const Polygon& lhs, const Polygon& rhs)
{
  auto lhs_max = std::max_element(lhs.points.cbegin(), lhs.points.cend(), comparePointsX);
  auto rhs_max = std::max_element(rhs.points.cbegin(), rhs.points.cend(), comparePointsX);

  return comparePointsX(*lhs_max, *rhs_max);
}

bool novikov::comparePolygonsMaxY(const Polygon& lhs, const Polygon& rhs)
{
  auto lhs_max = std::max_element(lhs.points.cbegin(), lhs.points.cend(), comparePointsY);
  auto rhs_max = std::max_element(rhs.points.cbegin(), rhs.points.cend(), comparePointsY);

  return comparePointsY(*lhs_max, *rhs_max);
}
