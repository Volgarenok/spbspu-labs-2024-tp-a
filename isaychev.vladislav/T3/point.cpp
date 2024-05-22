#include "point.hpp"
#include <iostream>
#include <delimeter.hpp>

std::istream & isaychev::operator>>(std::istream & in, Point & p)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  using dc = DelimChI;
  Point temp;
  in >> dc{'('} >> temp.x >> dc{';'} >> temp.y >> dc{')'};
  if (in)
  {
    p = temp;
  }

  return in;
}

std::ostream & isaychev::operator<<(std::ostream & out, const Point & p)
{
  out << "(" << p.x << ";" << p.y << ")";
  return out;
}
