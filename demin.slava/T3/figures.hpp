#ifndef FIGURES_HPP
#define FIGURES_HPP
#include <iostream>
#include <vector>

namespace demin
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
