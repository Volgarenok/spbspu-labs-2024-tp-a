#ifndef ADDITIONAL_COMMANDS_HPP
#define ADDITIONAL_COMMANDS_HPP

#include "datastruct.hpp"

namespace kuznetsov
{
  double getMaxOrMinArea(bool cur, double& maxOrMinArea, const Polygon& polygon);
  size_t getMaxOrMinVertexes(bool cur, size_t& maxOrMinVertexes, const Polygon& polygon);
  int getCountOfOddOrEvenVertexes(bool cur, int sum, const Polygon& polygon);
  int getCountWithNumVertexes(size_t num, int sum, const Polygon& polygon);
}

#endif

