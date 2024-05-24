#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <vector>

namespace zhalilov
{
  struct Point
  {
    int x, y;
  };

  struct Polygon
  {
    std::vector< Point > points;
  };
}

#endif
