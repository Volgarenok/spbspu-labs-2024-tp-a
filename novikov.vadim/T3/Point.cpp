#include "Point.hpp"

std::istream& novikov::operator>>(std::istream& in, Point& point)
{
  point = point;
  return in;
}
