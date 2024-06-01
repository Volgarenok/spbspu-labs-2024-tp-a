#ifndef INPUTSHAPES_HPP
#define INPUTSHAPES_HPP

#include <iosfwd>

namespace zhalilov
{
  struct Polygon;
  struct Point;
  std::istream &operator>>(std::istream &, Polygon &);
  std::istream &operator>>(std::istream &, Point &);
}

#endif
