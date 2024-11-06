#include "point.hpp"

bool chernikova::operator==(const Point& lhs, const Point& rhs)
{
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool chernikova::operator<(const Point & lhs, const Point & rhs)
{
  return lhs.x < rhs.x && lhs.y < rhs.y;
}

bool chernikova::operator>(const Point& lhs, const Point& rhs)
{
  return rhs < lhs;
}

bool chernikova::operator<=(const Point& lhs, const Point& rhs)
{
  return !(lhs > rhs);
}

bool chernikova::operator>=(const Point& lhs, const Point& rhs)
{
  return !(lhs < rhs);
}
