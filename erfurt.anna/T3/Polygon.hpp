#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <iostream>

namespace erfurt
{
  struct Point
  {
    int x;
    int y;
  };
  std::istream& operator>>(std::istream & in, Point & point);

  struct Polygon
  {
    std::vector<Point> points;
  };
  std::istream& operator>>(std::istream & in, Polygon & poly);
  bool isPointConsist(const Point & point, const Polygon & poly);
  double getArea(const Polygon & poly);
  bool isEqual(const Polygon & p1, const Polygon & p2);
}

#endif
