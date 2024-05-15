#include "predicates.hpp"

bool erohin::isXCoordinateLess(const Point & lhs, const Point & rhs)
{
  return lhs.x < rhs.x;
}

bool erohin::isYCoordinateLess(const Point & lhs, const Point & rhs)
{
  return lhs.y < rhs.y;
}
