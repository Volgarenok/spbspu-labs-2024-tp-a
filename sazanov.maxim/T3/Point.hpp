#ifndef POINT_HPP
#define POINT_HPP

#include <iosfwd>

namespace sazanov
{
  struct Point
  {
    int x;
    int y;
  };
  std::istream& operator>>(std::istream& in, Point& point);
}

#endif
