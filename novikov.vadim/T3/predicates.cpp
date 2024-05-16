#include "predicates.hpp"
#include <algorithm>

bool novikov::hasEvenVertexesCount(const Polygon& polygon)
{
  return polygon.points.size() % 2 == 0;
}

bool novikov::hasOddVertexesCount(const Polygon& polygon)
{
  return !hasEvenVertexesCount(polygon);
}

bool novikov::hasVertexesCount(const Polygon& polygon, size_t num)
{
  return polygon.points.size() == num;
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

bool novikov::isLayingIn(const minmax_pair_t& in_x, const minmax_pair_t& in_y, const minmax_pair_t& out_x, const minmax_pair_t& out_y)
{
  return in_x.first >= out_x.first && in_x.second <= out_x.second && in_y.first >= out_y.first && in_y.second <= out_y.second;
}
