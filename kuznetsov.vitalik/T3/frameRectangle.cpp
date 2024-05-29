#include "frameRectangle.hpp"
#include <algorithm>
#include "predicates.hpp"

bool kuznetsov::comparisonPointsByX(const Point& first, const Point& second)
{
  return second.x < first.x;
}

bool kuznetsov::comparisonPointsByY(const Point& first, const Point& second)
{
  return second.y < first.y;
}

std::pair< kuznetsov::Point, kuznetsov::Point > kuznetsov::getFramePoints(std::vector< Point >& polygon)
{
  auto minMaxX = std::minmax_element(polygon.begin(), polygon.end(), comparisonPointsByX);
  auto minMaxY = std::minmax_element(polygon.begin(), polygon.end(), comparisonPointsByY);
  return { { minMaxX.first->x, minMaxY.first->y }, { minMaxX.second->x, minMaxY.second->y } };
}

kuznetsov::Point kuznetsov::getMinPoint(std::pair< Point, Point > minMaxPoint)
{
  return minMaxPoint.first;
}

kuznetsov::Point kuznetsov::getMaxPoint(std::pair< Point, Point > minMaxPoint)
{
  return minMaxPoint.second;
}

std::pair< kuznetsov::Point, kuznetsov::Point > kuznetsov::getFrameRectangle(std::vector< Polygon >& polygon)
{
  std::vector< std::pair< Point, Point > > arrayMinMax;
  std::vector< Point > pointsAllFrameRectangle;
  std::transform(polygon.begin(), polygon.end(), std::back_inserter(arrayMinMax), getFramePoints);
  std::transform(arrayMinMax.begin(), arrayMinMax.end(), std::back_inserter(pointsAllFrameRectangle), getMinPoint);
  std::transform(arrayMinMax.begin(), arrayMinMax.end(), std::back_inserter(pointsAllFrameRectangle), getMaxPoint);
  return getFramePoints(pointsAllFrameRectangle);
}

bool kuznetsov::isPointBetwen(const Point& min, const Point& point, const Point& max)
{
  return (min.x <= point.x && min.y <= point.y && max.x >= point.x && max.y >= point.y);
}

bool kuznetsov::ifInFrameRectangle(const Polygon& polygon, std::pair< Point, Point > frameRectangle)
{
  auto operation = std::bind(isPointBetwen, frameRectangle.first, std::placeholders::_1, frameRectangle.second);
  size_t count = std::count_if(polygon.points.begin(), polygon.points.end(), operation);
  return count == polygon.points.size();
}
