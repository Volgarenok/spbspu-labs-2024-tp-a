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

std::ostream& belokurskaya::operator<<(std::ostream& out, const Point& point)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << '(' << point.x << ';' << point.y << ')';
  return out;
}
