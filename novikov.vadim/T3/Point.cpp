#include "Point.hpp"
#include <delimiterI.hpp>

std::istream& novikov::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  Point tmp{ 0, 0 };
  using chr_del = StrictCaseCharDelimiterI;
  in >> chr_del{ '(' } >> tmp.x >> chr_del{ ';' } >> tmp.y >> chr_del{ ')' };
  if (in)
  {
    point = tmp;
  }
  return in;
}
