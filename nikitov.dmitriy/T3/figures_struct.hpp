#ifndef FIGURES_STRUCT_HPP
#define FIGURES_STRUCT_HPP

#include <istream>
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

  double getPolygonArea(const Polygon& figure);

  bool operator==(const Point& lhs, const Point& rhs);
  std::istream& operator>>(std::istream& input, Point& value);
  std::istream& operator>>(std::istream& input, Polygon& value);
}
#endif
