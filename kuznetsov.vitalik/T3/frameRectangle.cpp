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

int kuznetsov::getPointsFrameX(const Polygon& polygon, std::function< bool() > func)
{
  int result = 0;

  auto maxOrMinX = std::minmax_element(polygon.points.begin(), polygon.points.end(), comparisonPointsByX);
  if (func)
  {
    result = maxOrMinX.second->x;
  }
  else
  {
    result = maxOrMinX.first->x;
  }
  return result;
}

int kuznetsov::getPointsFrameY(const Polygon& polygon, std::function< bool() > func)
{
  int result = 0;
  auto maxOrMinY = std::minmax_element(polygon.points.begin(), polygon.points.end(), comparisonPointsByY);
  if (func)
  {
    result = maxOrMinY.second->y;
  }
  else
  {
    result = maxOrMinY.first->y;
  }
  return result;
}

std::pair< kuznetsov::Point, kuznetsov::Point > kuznetsov::getFrameRectangle(std::vector< Polygon >& polygon)
{
  std::vector< int > vectorX;
  std::transform(polygon.begin(), polygon.end(), std::back_inserter(vectorX), std::bind(getPointsFrameX, std::placeholders::_1, isMax));
  std::transform(polygon.begin(), polygon.end(), std::back_inserter(vectorX), std::bind(getPointsFrameX, std::placeholders::_1, isMin));
  std::vector< int > vectorY;
  std::transform(polygon.begin(), polygon.end(), std::back_inserter(vectorY), std::bind(getPointsFrameX, std::placeholders::_1, isMax));
  std::transform(polygon.begin(), polygon.end(), std::back_inserter(vectorY), std::bind(getPointsFrameX, std::placeholders::_1, isMin));

  auto minMaxX = std::minmax_element(vectorX.begin(), vectorX.end());
  auto minMaxY = std::minmax_element(vectorY.begin(), vectorY.end());

  return std::make_pair(Point{ *minMaxX.first, *minMaxY.first }, Point{ *minMaxX.second, *minMaxY.second });
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
