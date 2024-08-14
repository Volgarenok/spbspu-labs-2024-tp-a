#ifndef POLYGON_HPP
#define POLYGON_HPP
#include <iostream>
#include <vector>

namespace zagrivnyy
{
  struct Point
  {
    int x, y;

    bool operator==(const Point &src) const;     // TODO: Remove it
    bool operator<(const Point &src) const;      // TODO: Remove it
    bool operator<=(const Point &src) const;     // TODO: Remove it
    bool operator>=(const Point &src) const;     // TODO: Remove it
  };

  std::istream &operator>>(std::istream &in, Point &src);

  struct Polygon
  {
    std::vector< Point > points;

    // TODO: Remove it
    bool operator==(const Polygon &src) const;
  };

  std::istream &operator>>(std::istream &in, Polygon &src);

  double getPolygonArea(const Polygon &p);
  void shoelaceFormula(const Point &p1, double &area);
}

#endif
