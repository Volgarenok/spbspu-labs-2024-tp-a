#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>

#include "../common/delimiter.hpp"

namespace kovtun
{
  struct Point
  {
    int x, y;
  };

  struct Polygon
  {
    std::vector< Point > points;
  };

  std::istream & operator>>(std::istream & in, Polygon & polygon);
}

#endif
