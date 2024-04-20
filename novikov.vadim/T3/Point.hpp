#ifndef POINT_HPP
#define POINT_HPP

#include <istream>

namespace novikov
{
  struct Point
  {
    int x, y;
  };
  std::istream& operator>>(std::istream& in, Point& point);
}

#endif
