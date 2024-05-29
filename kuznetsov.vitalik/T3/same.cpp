#include "same.hpp"
#include <algorithm>

bool kuznetsov::isSamePoint(const Point& delta, const Point& newPoint, int& current, const Polygon& polygon)
{
  Point newPointPlusDelta = { newPoint.x + delta.x, newPoint.y + delta.y };
  if (newPointPlusDelta.x == polygon.points[current].x &&
    newPointPlusDelta.y == polygon.points[current].y)
  {
    ++current;
    return true;
  }
  return false;
}

bool kuznetsov::areSame(const Polygon& firstShape, const Polygon& secondShape)
{
  if (firstShape.points.size() != secondShape.points.size())
  {
    return false;
  }

  int deltaX = secondShape.points[0].x - firstShape.points[0].x;
  int deltaY = secondShape.points[0].y - firstShape.points[0].y;
  Point delta{ deltaX, deltaY };
  using namespace std::placeholders;
  auto operation = std::bind(isSamePoint, delta, _1, 0, secondShape);
  return std::count_if(firstShape.points.cbegin(), firstShape.points.cend(), operation) == static_cast<int>(firstShape.points.size());
}
