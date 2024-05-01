#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <iostream>
#include <vector>

namespace kuzmina
{
  struct Point
  {
    int x, y;
  };

  struct Polygon
  {
    std::vector< Point > points;
  };

  std::istream& operator>>(std::istream&, Point&);
  std::ostream& operator<<(std::ostream&, const Point&);

  std::istream& operator>>(std::istream&, Polygon&);
  std::ostream& operator<<(std::ostream&, const Polygon&);
}

#endif
