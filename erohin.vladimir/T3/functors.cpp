#include "functors.hpp"
#include <cmath>

double erohin::evaluateArea::operator()(const Point & point)
{
  double area = std::abs((point.x - start.x) * (prev.y - start.y) - (prev.x - start.x) * (point.y - start.y)) / 2.0;
  prev = point;
  return area;
}

erohin::Point erohin::getFrameRectLeftLower::operator()(const Polygon & polygon)
{
  return getFrameRect(polygon).first;
}

erohin::Point erohin::getFrameRectRightUpper::operator()(const Polygon & polygon)
{
  return getFrameRect(polygon).second;
}
