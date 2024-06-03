#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <iostream>
#include <vector>

namespace kuzmina
{
  struct Point
  {
    int x, y;
  };
  bool comparePoints(const Point&, const Point&);

  struct Polygon
  {
    std::vector< Point > points;
    bool hasRightAngle() const;
  };
  bool comparePolygonPointsSize(const Polygon&, const Polygon&);
  double getArea(const Polygon& polygon);

  struct CountArea
  {
    Point point1;
    double operator()(double, const Point&, const Point&);
  };

  struct CountAngle
  {
    Point point1, point2;
    bool operator()(const Point&);
  };

  std::istream& operator>>(std::istream&, Point&);
  std::istream& operator>>(std::istream&, Polygon&);
}

#endif
