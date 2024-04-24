#include "Point.hpp"
#include <iostream>
#include <DelimiterI.hpp>
#include <StreamGuard.hpp>

std::istream& sazanov::operator>>(std::istream& in, sazanov::Point& point)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  Point temp{0, 0};
  in >> StrictCaseDelimiterI{'('} >> temp.x >> StrictCaseDelimiterI{';'} >> temp.y >> StrictCaseDelimiterI{')'};
  if (guard)
  {
    point = temp;
  }
  return in;
}

std::ostream& sazanov::operator<<(std::ostream& out, const sazanov::Point& point)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << '(' << point.x << ';' << point.y << ')';
  return out;
}
