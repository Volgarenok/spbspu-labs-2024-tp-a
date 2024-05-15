#include "predicates.hpp"
#include "polygon.hpp"

bool erohin::isXCoordinateLess(const Point & lhs, const Point & rhs)
{
  return lhs.x < rhs.x;
}

bool erohin::isYCoordinateLess(const Point & lhs, const Point & rhs)
{
  return lhs.y < rhs.y;
}

bool erohin::isVertexNumberEven(const Polygon & polygon)
{
  return (polygon.points.size() % 2 == 0);
}

bool erohin::isVertexNumberOdd(const Polygon & polygon)
{
  return !isVertexNumberEven(polygon);
}

bool erohin::isVertexNumber(const Polygon & polygon, size_t number)
{
  return (polygon.points.size() == number);
}

bool erohin::isLessByArea(const Polygon & lhs, const Polygon & rhs)
{
  return (getArea(lhs) < getArea(rhs));
}

bool erohin::isLessBySize(const Polygon & lhs, const Polygon & rhs)
{
  return (lhs.points.size() < rhs.points.size());
}

bool erohin::isLessByX(const Point & lhs, const Point & rhs)
{
  return (lhs.x < rhs.x);
}

bool erohin::isLessByY(const Point & lhs, const Point & rhs)
{
  return (lhs.y < rhs.y);
}

bool erohin::isLeftLower(const Point & lhs, const Point & rhs)
{
  return (lhs.y < rhs.y);
}
