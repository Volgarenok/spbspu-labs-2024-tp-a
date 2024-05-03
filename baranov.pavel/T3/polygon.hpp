#ifndef POLYGON_HPP
#define POLYGON_HPP
#include <vector>

namespace baranov
{
  struct Point
  {
    int x;
    int y;
  }

  struct Polygon
  {
    std::vector< Point > points;
  }
}

#endif
