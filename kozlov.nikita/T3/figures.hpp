#ifndef FIGURES_HPP
#define FIGURES_HPP
#include <vector>

namespace kozlov
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
