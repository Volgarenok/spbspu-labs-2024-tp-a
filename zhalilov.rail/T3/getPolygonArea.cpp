#include "getPolygonArea.hpp"

#include <algorithm>
#include <cstddef>
#include <functional>
#include <numeric>

#include "geometry.hpp"

namespace zhalilov
{
  double GaussSquareForwardStep(const Point &first, const Point &second)
  {
    return -(first.x * second.y);
  }

  double GaussSquareBacwardStep(const Point &first, const Point &second)
  {
    return first.y * second.x;
  }
}

double zhalilov::getPolygonArea(const Polygon &polygon)
{
  auto firstItBegin = polygon.points.cbegin();
  auto firstItEnd = polygon.points.cend();
  firstItBegin++;
  std::vector< Point > shiftedPoints;
  std::copy(firstItBegin, firstItEnd, std::back_inserter(shiftedPoints));
  shiftedPoints.push_back(*(--firstItBegin));

  std::vector< double > areas(polygon.points.size());
  using namespace std::placeholders;

  double area = 0.0;
  auto polyItCBegin = polygon.points.cbegin();
  auto polyItCEnd = polygon.points.cend();
  std::transform(polyItCBegin, polyItCEnd, shiftedPoints.cbegin(), areas.begin(), GaussSquareForwardStep);
  area = std::accumulate(areas.cbegin(), areas.cend(), 0.0);
  std::transform(polyItCBegin, polyItCEnd, shiftedPoints.cbegin(), areas.begin(), GaussSquareBacwardStep);
  area += std::accumulate(areas.cbegin(), areas.cend(), 0.0);
  area *= 0.5;
  return std::abs(area);
}
