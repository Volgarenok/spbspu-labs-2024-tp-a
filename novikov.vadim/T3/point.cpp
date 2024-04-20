#include "point.hpp"
#include <delimiterI.hpp>

std::istream& novikov::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  Point tmp{ 0, 0 };
  using del = StrictCaseCharDelimiterI;
  in >> del{ '(' } >> tmp.x >> del{ ';' } >> tmp.y >> del{ ')' };
  if (in)
  {
    point = tmp;
  }
  return in;
}
