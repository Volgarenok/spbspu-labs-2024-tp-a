#ifndef SAME_HPP
#define SAME_HPP

#include "datastruct.hpp"

namespace kuznetsov
{
  bool isSamePoint(const Point& delta, const Point& newPoint, int& current, const Polygon& polygon);
  bool areSame(const Polygon& firstPolygon, const Polygon& secondPolygon);
}

#endif
