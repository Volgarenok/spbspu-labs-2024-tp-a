#ifndef PREDICATES_HPP
#define PREDICATES_HPP

#include "polygon.hpp"

namespace erohin
{
  bool isXCoordinateLess(const Point & lhs, const Point & rhs);
  bool isYCoordinateLess(const Point & lhs, const Point & rhs);
  bool isVertexNumberEven(const Polygon & polygon);
  bool isVertexNumberOdd(const Polygon & polygon);
  bool isVertexNumber(const Polygon & polygon, size_t number);
}

#endif
