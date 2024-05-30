#ifndef POINT_HPP
#define POINT_HPP

#include <istream>

namespace ibragimov
{
  struct Point
  {
    int x, y;
  };
  std::istream& operator>>(std::istream&, Point&);
  int getX(const Point&);
  int getY(const Point&);
}

#endif
