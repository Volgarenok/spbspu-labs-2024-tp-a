#ifndef POLYGON_HPP
#define POLYGON_HPP
#include <iostream>
#include <vector>

namespace zagrivnyy
{
  struct Point
  {
    int x, y;
  };

  std::istream &operator>>(std::istream &in, Point &src);

  struct Polygon
  {
    std::vector< Point > points;

    double getArea() const;
  };

  std::istream &operator>>(std::istream &in, Polygon &src);
}

#endif
