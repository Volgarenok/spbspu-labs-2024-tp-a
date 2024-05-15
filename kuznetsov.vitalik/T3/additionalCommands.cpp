#include "additionalCommands.hpp"
#include <utility>
#include <numeric>
#include <functional>

double kuznetsov::getMaxOrMinArea(bool cur, double& maxOrMinArea, const Polygon& polygon)
{
  double area = getAreaPolygon(polygon);
  if (cur)
  {
    if (area > maxOrMinArea)
    {
      maxOrMinArea = area;
      return area;
    }
  }
  else
  {
    if (area < maxOrMinArea)
    {
      maxOrMinArea = area;
      return area;
    }
  }
  return maxOrMinArea;
}

size_t kuznetsov::getMaxOrMinVertexes(bool cur, size_t& maxOrMinVertexes, const Polygon& polygon)
{
  size_t vertexes = polygon.points.size();
  if (cur)
  {
    if (vertexes > maxOrMinVertexes)
    {
        maxOrMinVertexes = vertexes;
        return vertexes;
    }
  }
  else
  {
    if (vertexes < maxOrMinVertexes)
    {
      maxOrMinVertexes = vertexes;
      return vertexes;
    }
  }
  return maxOrMinVertexes;
}

int kuznetsov::getCountOfOddOrEvenVertexes(bool cur, int sum, const Polygon& polygon)
{
  if (!cur && polygon.points.size() % 2 == 1)
  {
    return sum + 1;
  }
  else if (cur && polygon.points.size() % 2 == 0)
  {
    return sum + 1;
  }
  else
  {
    return sum;
  }
}

int kuznetsov::getCountWithNumVertexes(size_t num, int sum, const Polygon& polygon)
{
  if (num == polygon.points.size())
  {
    return sum + 1;
  }
  return sum;
}

kuznetsov::Point& kuznetsov::comparisonPoints(bool cur, Point& point, const Point& newPoint)
{
  if (cur)
  {
    if (point.x < newPoint.x)
    {
      point.x = newPoint.x;
    }
    if (point.y < newPoint.y)
    {
      point.y = newPoint.y;
    }
  }
  else
  {
    if (point.x > newPoint.x)
    {
      point.x = newPoint.x;
    }
    if (point.y > newPoint.y)
    {
      point.y = newPoint.y;
    }
  }
  return point;
}

kuznetsov::Point& kuznetsov::getMinOrMaxPoint(bool cur, Point& framePoint, const Polygon& polygon)
{
  using namespace std::placeholders;
  auto operation = std::bind(comparisonPoints, cur, _1, _2);
  framePoint = std::accumulate(polygon.points.cbegin() , polygon.points.cend(), framePoint, operation);
  return framePoint;
}

kuznetsov::Point kuznetsov::getFramePoint(bool cur, Point& framePoint, std::vector< Polygon >& polygon)
{
  using namespace std::placeholders;
  auto operation = std::bind(getMinOrMaxPoint, cur, _1, _2);
  framePoint = std::accumulate(polygon.cbegin(), polygon.cend(), polygon[0].points[0], operation);
  return framePoint;
}

bool kuznetsov::comparisonWithTwoPoints(bool& cur, Point& min, Point& max, const Point& newPoint)
{
  if (!cur)
  {
    return false;
  }
  if (min <= newPoint && max >= newPoint)
  {
    return true;
  }
  else
  {
    cur = false;
    return false;
  }
}

bool kuznetsov::isInFrame(Point& min, Point& max, Polygon& polygon)
{
  using namespace std::placeholders;
  bool flag = true;
  auto operation = std::bind(comparisonWithTwoPoints, true, min, max, _2);
  flag = std::accumulate(polygon.points.cbegin(), polygon.points.cend(), true, operation);
  return flag;
}
