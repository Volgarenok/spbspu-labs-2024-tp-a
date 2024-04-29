#include "Point.hpp"
#include <iostream>
#include <DelimiterI.hpp>

std::istream& sazanov::operator>>(std::istream& in, sazanov::Point& point)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  Point temp{0, 0};
  in >> StrictCaseDelimiterI{'('} >> temp.x >> StrictCaseDelimiterI{';'} >> temp.y >> StrictCaseDelimiterI{')'};
  if (in)
  {
    point = temp;
  }
  return in;
}

std::ostream& sazanov::operator<<(std::ostream& out, const sazanov::Point& point)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << '(' << point.x << ';' << point.y << ')';
  return out;
}

bool sazanov::Point::operator==(const sazanov::Point& rhs) const
{
  return x == rhs.x && y == rhs.y;
}

sazanov::Point& sazanov::Point::operator=(const sazanov::Point& rhs)
{
  x = rhs.x;
  y = rhs.y;
  return *this;
}
