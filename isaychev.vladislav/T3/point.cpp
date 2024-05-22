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
  in >> dc{'('} >> p.x >> dc{';'} >> p.y >> dc{')'};

  return in;
}
