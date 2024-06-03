#include "same.hpp"
#include <algorithm>

bool kuznetsov::isSamePoint(const Point& delta, const Point& newPoint, int& current, const Polygon& polygon)
{
  Point newPointPlusDelta = { newPoint.x + delta.x, newPoint.y + delta.y };
  if (newPointPlusDelta.x == polygon.points[current].x && newPointPlusDelta.y == polygon.points[current].y)
  {
    ++current;
    return true;
  }
  return false;
}

bool kuznetsov::areSame(const Polygon& firstPolygon, const Polygon& secondPolygon)
{
  if (firstPolygon.points.size() != secondPolygon.points.size())
  {
    return false;
  }

  int deltaX = secondPolygon.points[0].x - firstPolygon.points[0].x;
  int deltaY = secondPolygon.points[0].y - firstPolygon.points[0].y;
  Point delta{ deltaX, deltaY };
  using namespace std::placeholders;
  auto operation = std::bind(isSamePoint, delta, _1, 0, secondPolygon);
  int numberOfPoints = std::distance(firstPolygon.points.begin(), firstPolygon.points.end());
  return std::count_if(firstPolygon.points.cbegin(), firstPolygon.points.cend(), operation) == numberOfPoints;
}
