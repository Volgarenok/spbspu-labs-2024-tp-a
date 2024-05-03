#ifndef POLYGON_H
#define POLYGON_H

#include <vector>

namespace kornienko
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
