#include "polygon.hpp"

std::istream& ravinskij::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = ravinskij::CharDelimeter;
  in >> del{'('} >> point.x >> del{';'} >> point.y >> del{')'};
  return in;
}

std::ostream& ravinskij::operator<<(std::ostream& out, const Point& point)
{
  out << '(' << point.x << ';' << point.y << ')';
  return out;
}
