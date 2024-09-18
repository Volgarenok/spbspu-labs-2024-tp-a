#include "getPolygonArea.hpp"

#include <algorithm>
#include <cstddef>
#include <functional>
#include <numeric>

#include "geometry.hpp"

namespace zhalilov
{
  double doGaussSquareForwardStep(const Point &first, const Point &second)
  {
    return -(first.x * second.y);
  }

  double doGaussSquareBacwardStep(const Point &first, const Point &second)
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
  std::transform(polyItCBegin, polyItCEnd, shiftedPoints.cbegin(), areas.begin(), doGaussSquareForwardStep);
  area = std::accumulate(areas.cbegin(), areas.cend(), 0.0);
  std::transform(polyItCBegin, polyItCEnd, shiftedPoints.cbegin(), areas.begin(), doGaussSquareBacwardStep);
  area += std::accumulate(areas.cbegin(), areas.cend(), 0.0);
  area *= 0.5;
  return std::abs(area);
}
