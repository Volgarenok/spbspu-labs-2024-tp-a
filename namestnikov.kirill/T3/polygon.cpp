#include "polygon.hpp"
#include <delimeter.hpp>

std::istream & namestnikov::operator>>(std::istream & in, namestnikov::Point & point)
{
  using delC = DelimeterChar;
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  Point tempPoint = {0, 0};
  in >> delC{'('} >> tempPoint.x >> delC{';'} >> tempPoint.y >> delC{')'};
  if (in)
  {
    point = tempPoint;
  }
  return in;
}

std::ostream & namestnikov::operator<<(std::ostream & out, const namestnikov::Point & point)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << '(' << point.x << ';' << point.y << ')';
  return out;
}