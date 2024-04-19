#include "point.hpp"

std::istream& ibragimov::operator>>(std::istream& in, Point& rhs)
{
  std::istream::sentry guard(in);
  if (!guard) {
    return in;
  }
  in >> rhs.x >> rhs.y;
  if (!in)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
