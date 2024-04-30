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
    bool operator==(const Point & other) const;
  };
  std::istream & operator>>(std::istream & in, Point & point);

  struct Polygon
  {
    std::vector<Point> points;
    double getArea() const;
    bool operator==(const Polygon & poly) const;
  };
  std::istream& operator>>(std::istream & in, Polygon & poly);
  bool isPointConsist(const Point & point, const Polygon & poly);

  struct AccumulatePolygonArea
  {
    Point p0;
    double operator()(double area, const Point & p1, const Point & p2);
  };
}

#endif
