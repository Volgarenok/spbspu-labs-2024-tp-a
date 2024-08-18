#include "filters.hpp"

#include <algorithm>

bool demin::odd(const Polygon &p)
{
  return p.points.size() % 2;
}

bool demin::even(const Polygon &p)
{
  return !odd(p);
}

