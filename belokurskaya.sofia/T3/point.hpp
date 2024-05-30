#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>

namespace belokurskaya
{
  struct Point
  {
    int x, y;
  };

  std::istream& operator>>(std::istream& in, Point& point);
  bool operator==(const Point& lhs, const Point& rhs);
}

#endif
