#include "point.hpp"

#include "inputFormatters.hpp"

std::istream& belokurskaya::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  Point tmp;
  in >> DelimiterI{ '(' } >> tmp.x >> DelimiterI{ ';' } >> tmp.y >> DelimiterI{ ')' };
  if (!in.fail())
  {
    point = tmp;
  }
  return in;
}

bool belokurskaya::operator==(const Point& lhs, const Point& rhs)
{
  return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}
