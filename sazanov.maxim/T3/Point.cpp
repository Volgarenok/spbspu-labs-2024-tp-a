#include "Point.hpp"
#include <iostream>
#include <DelimiterI.hpp>

std::istream& sazanov::operator>>(std::istream& in, Point& point)
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

std::ostream& sazanov::operator<<(std::ostream& out, const Point& point)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << '(' << point.x << ';' << point.y << ')';
  return out;
}

bool sazanov::operator==(const Point& lhs, const Point& rhs)
{
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool sazanov::operator<(const Point& lhs, const Point& rhs)
{
  if (lhs.x != rhs.x)
  {
    return lhs.x < rhs.x;
  }
  return lhs.y < rhs.y;
}
