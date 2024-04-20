#ifndef FIGURES_STRUCT_HPP
#define FIGURES_STRUCT_HPP

#include <vector>
#include <istream>

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

  std::istream& operator>>(std::istream& input, Point& value);
  std::istream& operator>>(std::istream& input, Polygon& value);
}
#endif
