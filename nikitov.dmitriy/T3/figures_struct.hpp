#ifndef FIGURES_STRUCT_HPP
#define FIGURES_STRUCT_HPP

#include <vector>

namespace nikitov
{
  struct Point
  {
    int x;
    int y;
  };

  struct Polygon
  {
    std::vector< Point > points;
  };
}
#endif