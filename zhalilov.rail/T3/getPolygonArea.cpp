#include "getPolygonArea.hpp"

#include <algorithm>
#include <cstddef>
#include <functional>
#include <numeric>

#include "geometry.hpp"

namespace zhalilov
{
  enum class StepType
  {
    Forward,
    Backward
  };

  double GaussSquare(StepType type, const Point &first, const Point &second)
  {
    if (type == StepType::Forward)
    {
      return -(first.x * second.y);
    }
    return first.y * second.x;
  }
}

double zhalilov::getPolygonArea(const Polygon &polygon)
{
  auto firstItBegin = polygon.points.cbegin();
  auto firstItEnd = polygon.points.cend();
  firstItBegin++;
  std::vector < Point > shiftedPoints;
  std::copy(firstItBegin, firstItEnd, std::back_inserter(shiftedPoints));
  shiftedPoints.push_back(*(--firstItBegin));

  std::vector < double > areas(polygon.points.size());
  using namespace std::placeholders;
  auto forwardStep = std::bind(GaussSquare, StepType::Forward, _1, _2);
  auto backwardStep = std::bind(GaussSquare, StepType::Backward, _1, _2);

  double area = 0.0;
  std::transform(polygon.points.cbegin(), polygon.points.cend(), shiftedPoints.cbegin(), areas.begin(), forwardStep);
  area = std::accumulate(areas.cbegin(), areas.cend(), 0.0);
  std::transform(polygon.points.cbegin(), polygon.points.cend(), shiftedPoints.cbegin(), areas.begin(), backwardStep);
  area += std::accumulate(areas.cbegin(), areas.cend(), 0.0);
  area *= 0.5;
  return area;
}
