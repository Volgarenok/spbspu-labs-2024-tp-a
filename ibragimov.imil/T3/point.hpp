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
}

#endif
