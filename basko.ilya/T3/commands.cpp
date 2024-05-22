#include "commands.h"
#include <functional>
#include <iomanip>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <string>
#include <scopeGuard.hpp>
#include "polygon.hpp"

bool isOdd(const basko::Polygon& polygon)
{
  return polygon.points.size() % 2;
}

bool isEven(const basko::Polygon& polygon)
{
  return !(polygon.points.size() % 2);
}
