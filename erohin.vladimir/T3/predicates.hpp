#ifndef PREDICATES_HPP
#define PREDICATES_HPP

#include "polygon.hpp"

namespace erohin
{
  bool isXCoordinateLess(const Point & lhs, const Point & rhs);
  bool isYCoordinateLess(const Point & lhs, const Point & rhs);
  bool isFrameRectXCoordinateLess(const Polygon & lhs, const Polygon & rhs);
  bool isFrameRectYCoordinateLess(const Polygon & lhs, const Polygon & rhs);
  bool isFrameRectXCoordinateNotGreater(const Polygon & lhs, const Polygon & rhs);
  bool isFrameRectYCoordinateNotGreater(const Polygon & lhs, const Polygon & rhs);
}

#endif
