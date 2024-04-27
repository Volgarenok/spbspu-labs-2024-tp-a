#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <iostream>
#include <vector>

namespace namestnikov
{
  struct Point
  {
    int x;
    int y;
  };
  std::istream & operator>>(std::istream & in, Point & point);
  std::ostream & operator<<(std::ostream & out, const Point & point);

  struct Polygon
  {
    std::vector< Point > points;
  };
  std::istream & operator>>(std::istream & in, Polygon & polygon);
  std::ostream & operator<<(std::ostream & out, const Polygon & polygon);
}

#endif