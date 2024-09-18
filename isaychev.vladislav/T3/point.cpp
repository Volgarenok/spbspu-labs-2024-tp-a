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
  out << '(' << p.x << ';' << p.y << ')';
  return out;
}

bool isaychev::operator==(const Point & p1, const Point & p2)
{
  return p1.x == p2.x && p1.y == p2.y;
}

bool isaychev::operator<(const Point & p1, const Point & p2)
{
  return p1.x < p2.x && p1.y < p2.y;
}
