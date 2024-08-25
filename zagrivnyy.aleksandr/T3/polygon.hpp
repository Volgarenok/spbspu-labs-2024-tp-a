#ifndef POLYGON_HPP
#define POLYGON_HPP
#include <iostream>
#include <vector>

namespace zagrivnyy
{
  struct Point
  {
    int x, y;
  };

  std::istream &operator>>(std::istream &in, Point &src);
  bool operator==(const Point &first, const Point &second);
  bool operator<(const Point &first, const Point &second);
  bool operator<=(const Point &first, const Point &second);
  bool operator>=(const Point &first, const Point &second);

  struct Polygon
  {
    std::vector< Point > points;
  };

  std::istream &operator>>(std::istream &in, Polygon &src);
  bool operator==(const Polygon &first, const Polygon &second);

  double getPolygonArea(const Polygon &p);
  void shoelaceFormula(const Point &p1, double &area);
}

#endif
