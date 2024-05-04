#ifndef ADDITIONAL_COMMANDS_HPP
#define ADDITIONAL_COMMANDS_HPP

#include "datastruct.hpp"

namespace kuznetsov
{
  double getMaxOrMinArea(bool cur, double& maxOrMinArea, const Polygon& polygon);
  int getMaxOrMinVertexes(bool cur, int& maxOrMinVertexes, const Polygon& polygon);
}

#endif

