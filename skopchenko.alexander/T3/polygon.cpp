#include "polygon.hpp"


bool skopchenko::operator==(const Point& first, const Point& second)
{
  return ((first.x == second.x) && (first.y == second.y));
}

bool skopchenko::operator<(const Point& first, const Point& second)
{
  return ((first.x < second.x) && (first.y < second.y));
}

bool skopchenko::operator<=(const Point& first, const Point& second)
{
  return ((first.x <= second.x) && (first.y <= second.y));
}

bool skopchenko::operator>=(const Point& first, const Point& second)
{
  return ((first.x >= second.x) && (first.y >= second.y));
}
