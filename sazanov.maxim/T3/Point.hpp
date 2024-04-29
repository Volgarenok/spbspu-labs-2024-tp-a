#ifndef POINT_HPP
#define POINT_HPP

#include <iosfwd>

namespace sazanov
{
  struct Point
  {
    int x;
    int y;

    Point& operator=(const Point& rhs);
    bool operator==(const Point& rhs) const;
  };
  std::istream& operator>>(std::istream& in, Point& point);
  std::ostream& operator<<(std::ostream& out, const Point& point);
}

#endif
