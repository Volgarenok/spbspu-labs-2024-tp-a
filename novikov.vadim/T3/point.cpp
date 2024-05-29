#include "point.hpp"
#include <ostream>
#include <delimiterI.hpp>

std::istream& novikov::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  Point temp{ 0, 0 };
  using del = StrictCaseCharDelimiterI;
  in >> del{ '(' } >> temp.x >> del{ ';' } >> temp.y >> del{ ')' };
  if (in)
  {
    point = temp;
  }

  return in;
}

std::ostream& novikov::operator<<(std::ostream& out, const Point& point)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << '(' << point.x << ';' << point.y << ')';
  return out;
}

bool novikov::operator==(const Point& lhs, const Point& rhs)
{
  return lhs.x == rhs.x && lhs.y == rhs.y;
}
