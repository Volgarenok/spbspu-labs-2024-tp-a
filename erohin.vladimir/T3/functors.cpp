#include "functors.hpp"
#include <cmath>

double erohin::evaluateArea::operator()(const Point & point)
{
  double area = std::abs((point.x - start.x) * (prev.y - start.y) - (prev.x - start.x) * (point.y - start.y)) / 2.0;
  prev = point;
  return area;
}

bool erohin::isRightAngle::operator()(const Point & point)
{
  size_t scalar_miltiply = std::abs((point.x - center.x) * (prev.x - center.x) + (point.y - center.y) * (prev.y - center.y));
  prev = center;
  center = point;
  return !scalar_miltiply;
}

erohin::Point erohin::getFrameRectLeftLower::operator()(const Polygon & polygon)
{
  return getFrameRect(polygon).first;
}

erohin::Point erohin::getFrameRectRightUpper::operator()(const Polygon & polygon)
{
  return getFrameRect(polygon).second;
}
