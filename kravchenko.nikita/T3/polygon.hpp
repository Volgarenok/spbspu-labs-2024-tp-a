#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <iostream>
#include <vector>

namespace kravchenko
{
  struct Point
  {
    int x;
    int y;
  };
  bool operator==(const Point& lhs, const Point& rhs);
  std::istream& operator>>(std::istream& in, Point& p);

  struct Polygon
  {
    std::vector< Point > points;
  };
  double getArea(const Polygon& p);
  bool isIdentical(const Polygon& p1, const Polygon& p2);
  bool hasRightAngle(const Polygon& p);
  std::istream& operator>>(std::istream& in, Polygon& p);

  struct AccumulatePolygonArea
  {
    Point p1;
    double operator()(double acc, const Point& p2, const Point& p3);
  };

  struct RightAnglePred
  {
    Point side1;
    Point apex;
    bool operator()(const Point& side2);
  };
}

#endif
