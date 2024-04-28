#ifndef POINT_HPP
#define POINT_HPP

#include <istream>

namespace novikov
{
  struct Point
  {
    int x, y;
  };
  std::istream& operator>>(std::istream& in, Point& rhs);
  std::ostream& operator<<(std::ostream& out, const Point& rhs);
  bool operator==(const Point& lhs, const Point& rhs);

  struct AreaAccumulator
  {
    Point p1;
    double operator()(double val, const Point& p2, const Point& p3);
  };
}

#endif
