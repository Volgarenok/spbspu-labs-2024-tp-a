#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iostream>
#include <vector>
#include "StreamGuard.hpp"
#include "polygon.hpp"

namespace feofanova
{
  double getArea(const Polygon& polygon);
  bool isAreaLess(const Polygon& p1, const Polygon& p2);
  bool Perms(const Polygon& p1, const Polygon& p2);
}
#endif
