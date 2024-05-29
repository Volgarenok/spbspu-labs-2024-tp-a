#ifndef PREDICATES_HPP
#define PREDICATES_HPP

#include "datastruct.hpp"

namespace kuznetsov
{
  bool isEvenVertexes(const Polygon& polygon);
  bool isOddVertexes(const Polygon& polygon);
  bool isNumEqualSize(const Polygon& polygon, size_t num);
  bool isMax();
  bool isMin();
}

#endif
