#include "Polygon.hpp"

std::istream& stepanchenko::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = DelimiterI;
  Point t_point{ 0, 0 };
  in >> del{ '(' } >> t_point.x >> del{ ';' } >> t_point.y >> del{ ')' };
  if (in)
  {
  point = t_point;
  }
  return in;
}

std::istream& stepanchenko::operator>>(std::istream& in, Polygon& polygon);
