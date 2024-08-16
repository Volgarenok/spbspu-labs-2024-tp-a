#ifndef POINT_HPP
#define POINT_HPP

#include <iosfwd>

namespace isaychev
{
  struct Point
  {
    int x, y;
  };

  std::istream & operator>>(std::istream & in, Point & p);
  std::ostream & operator<<(std::ostream & out, const Point & p);
  bool operator==(const Point & p1, const Point & p2);
  bool operator<(const Point & p1, const Point & p2);
}

#endif
