#ifndef FIGURES_HPP
#define FIGURES_HPP
#include <iostream>
#include <vector>

namespace timchishina
{
  struct Point
  {
    int x, y;
  };
  std::istream& operator>>(std::istream& in, Point& point);

  struct Polygon
  {
    std::vector< Point > points;
  };
  std::istream& operator>>(std::istream& in, Polygon& poly);
}
#endif
