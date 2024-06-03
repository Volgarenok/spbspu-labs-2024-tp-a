#ifndef POINT_HPP
#define POINT_HPP

namespace chernikova
{
  struct Point
  {
    int x, y;
  };

  bool operator==(const Point& lhs, const Point& rhs);
  bool operator<(const Point& lhs, const Point& rhs);
  bool operator>(const Point& lhs, const Point& rhs);
  bool operator<=(const Point& lhs, const Point& rhs);
  bool operator>=(const Point& lhs, const Point& rhs);
}

#endif
