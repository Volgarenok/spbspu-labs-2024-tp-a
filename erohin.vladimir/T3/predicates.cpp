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
  return (polygon.size() % 2 == 0);
}

bool erohin::isVertexNumberOdd(const Polygon & polygon)
{
  return !isVertexNumberEven(context);
}

bool erohin::isVertexNumber(const Polygon & polygon, size_t number)
{
  return (polygon.size() == number);
}
