#include <iostream>

#include "polygon.hpp"

std::istream & kornienko::operator>>(std::istream & in, Point & point)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = Delimeter;
  in >> del{ '(' } >> point.x >> del{ ';' } >> point.y >> del{ ')' };
  return in;
}

std::ostream & kornienko::operator<<(std::ostream & out, const Point & point)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << "(" << point.x << ";" << point.y << ")";
  return out;
}
