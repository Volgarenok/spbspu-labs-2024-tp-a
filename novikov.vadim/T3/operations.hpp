#ifndef OPERATIONS_HPP
#define OPERATIONS_HPP

#include "polygon.hpp"

namespace novikov
{
  double hasEvenVertexesCount(const Polygon& polygon);
  double hasOddVertexesCount(const Polygon& polygon);
  double hasVertexesCount(const Polygon& polygon, size_t num);
  double reverseValue(const Polygon& polygon);
}

#endif
