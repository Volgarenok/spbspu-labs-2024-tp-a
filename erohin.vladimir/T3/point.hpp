#ifndef POINT_HPP
#define POINT_HPP

#include <iosfwd>

namespace erohin
{
  struct Point
  {
    int x, y;
  };

  std::istream & operator>>(std::istream & input, Point & point);
  std::ostream & operator<<(std::ostream & output, const Point & point);
  bool isLessByX(const Point & lhs, const Point & rhs);
  bool isLessByY(const Point & lhs, const Point & rhs);
}

#endif
