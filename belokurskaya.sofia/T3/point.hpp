#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>

namespace belokurskaya
{
  struct Point
  {
    int x, y;
    bool operator==(const Point& other) const;
  };

  std::istream& operator>>(std::istream& in, Point& point);
  std::ostream& operator<<(std::ostream& out, const Point& point);
}

#endif
