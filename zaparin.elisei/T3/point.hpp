#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>

namespace zaparin
{
  struct Point
  {
    int x, y;
  };

  std::istream& operator>>(std::istream& fin, Point& point);

  bool operator==(const Point& p1, const Point& p2);

  bool operator<(const Point& p1, const Point& p2);
  bool operator<=(const Point& p1, const Point& p2);
  bool operator>=(const Point& p1, const Point& p2);

  double getLength(const Point& p1, const Point& p2);
}

#endif

