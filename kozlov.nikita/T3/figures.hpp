#ifndef FIGURES_HPP
#define FIGURES_HPP
#include <iostream>
#include <vector>

namespace kozlov
{
  struct Point
  {
    int x, y;
  };
  std::istream& operator>>(std::istream& in, Point& point);
  bool operator<(const Point& p1, const Point& p2);
  bool operator==(const Point& p1, const Point& p2);

  struct Polygon
  {
    std::vector< Point > points;
  };
  std::istream& operator>>(std::istream& in, Polygon& poly);
  bool operator==(const Polygon& p1, const Polygon& p2);
}
#endif
