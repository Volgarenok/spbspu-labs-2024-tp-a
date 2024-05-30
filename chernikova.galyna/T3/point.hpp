#ifndef POINT_HPP
#define POINT_HPP

namespace chernikova
{
  struct Point
  {
    Point() : x(0), y(0)
    {}
    int x;
    int y;
  };

  bool operator==(const Point& lhs, const Point& rhs);
  bool operator<(const Point& lhs, const Point& rhs);
  bool operator>(const Point& lhs, const Point& rhs);
  bool operator<=(const Point& lhs, const Point& rhs);
  bool operator>=(const Point& lhs, const Point& rhs);
}

#endif
