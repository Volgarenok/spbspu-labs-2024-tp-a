#ifndef POLYGON_H
#define POLYGON_H

#include <iostream>
#include <vector>

namespace kartamyshev
{
  struct Point
  {
    int x, y;
  };
  bool operator==(const Point& dot1, const Point& dot2);
  bool operator<(const Point& dot1, const Point& dot2);
  bool operator<=(const Point& dot1, const Point& dot2);

  std::istream& operator>>(std::istream& in, Point& value);

  struct Polygon
  {
    std::vector< Point > points;
  };
  double getArea(const Polygon& polygon);

  std::istream& operator>>(std::istream& in, Polygon& value);

}

#endif
