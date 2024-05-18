#include "pointCompare.hpp"

#include "geometry.hpp"

bool zhalilov::operator==(const Point &first, const Point &second)
{
  return first.x == second.x && first.y == second.y;
}

bool zhalilov::operator<(const Point &first, const Point &second)
{
  if (first.x == second.x)
  {
    return first.y < second.y;
  }
  return first.x < second.x;
}
