#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <istream>
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
  std::istream& operator>>(std::istream&, Polygon&);
}

#endif
