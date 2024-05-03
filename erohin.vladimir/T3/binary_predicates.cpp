#include "binary_predicates.hpp"

bool erohin::isXCoordinateLess(const Point & lhs, const Point & rhs)
{
  return lhs.x < rhs.x;
}

bool erohin::isYCoordinateLess(const Point & lhs, const Point & rhs)
{
  return lhs.y < rhs.y;
}

bool erohin::isFrameRectXCoordinateLess(const Polygon & lhs, const Polygon & rhs)
{
  return isXCoordinateLess(lhs.getFrameRect().first, rhs.getFrameRect().first);
}

bool erohin::isFrameRectYCoordinateLess(const Polygon & lhs, const Polygon & rhs)
{
  return isYCoordinateLess(lhs.getFrameRect().first, rhs.getFrameRect().first);
}

bool erohin::isFrameRectXCoordinateNotGreater(const Polygon & lhs, const Polygon & rhs)
{
  Point lhs_point = lhs.getFrameRect().second;
  Point rhs_point = rhs.getFrameRect().second;
  return isXCoordinateLess(lhs_point, rhs_point) && lhs_point.x == rhs_point.x;
}

bool erohin::isFrameRectYCoordinateNotGreater(const Polygon & lhs, const Polygon & rhs)
{
  Point lhs_point = lhs.getFrameRect().second;
  Point rhs_point = rhs.getFrameRect().second;
  return isYCoordinateLess(lhs_point, rhs_point) && lhs_point.y == rhs_point.y;
}
