#include "polygon.hpp"
#include <iostream>
#include "delimiter.hpp"

std::istream& ayupov::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using DelC = DelimiterChar;
  in >> DelC{'('} >> point.x >> DelC{';'} >> point.y >> DelC{')'};
  return in;
}
std::ostream& ayupov::operator<<(std::ostream& out, const Point& point)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << '(' << point.x << ';' << point.y << ')';
  return out;
}