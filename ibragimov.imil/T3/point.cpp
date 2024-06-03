#include "point.hpp"

#include <iostream>
#include "label.hpp"
#include "strategies.hpp"
#include "streamGuard.hpp"

std::istream& ibragimov::operator>>(std::istream& in, Point& rhs)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using LabelI = formatters::LabelI< formatters::CaseSensitive >;
  StreamGuard sguard(in);
  in >> std::noskipws;
  in >> LabelI{"("} >> rhs.x >> LabelI{";"} >> rhs.y >> LabelI{")"};
  if (!in)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
int ibragimov::getX(const Point& value)
{
  return value.x;
}
int ibragimov::getY(const Point& value)
{
  return value.y;
}
