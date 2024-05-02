#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <iosfwd>

namespace erohin
{
  struct Point
  {
    int x, y;
  };
  std::istream & operator>>(std::istream & input, Point & point);

  struct Polygon
  {
    std::vector< Point > points;
  };
  std::istream & operator>>(std::istream & input, Polygon & polygon);
}

#endif
