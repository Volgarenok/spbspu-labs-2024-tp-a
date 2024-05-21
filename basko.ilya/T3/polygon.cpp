#include "polygon.hpp"
#include <delimiters.hpp>

std::istream& basko::operator>>(std::istream& in, Point& point)
{
  using delChar = DelimiterChar;
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  Point temp = { 0, 0 };
  in >> delChar{ '(' } >> temp.x >> delChar{ ';' } >> temp.y >> delChar{ ')' };
  if (in)
  {
    point = temp;
  }
  return in;
}

std::ostream& basko::operator<<(std::ostream& out, const Point& point)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << '(' << point.x << ';' << point.y << ')';
  return out;
}
