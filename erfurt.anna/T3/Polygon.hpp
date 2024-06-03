#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <iostream>
#include <algorithm>

namespace erfurt
{
  struct Point
  {
    int x;
    int y;
  };
  std::istream & operator>>(std::istream & in, Point & point);
  bool operator==(const Point & point1, const Point & point2);

  struct Polygon
  {
    std::vector< Point > points;
  };
  std::istream & operator>>(std::istream & in, Polygon & poly);
  double getArea(const Polygon & poly);
  double getAreaPolygons(const std::vector< Polygon > & pols);
  bool isPointIn(const Point & point, const Polygon & poly);
  bool isEqual(const Polygon & p1, const Polygon & p2);
}

#endif
