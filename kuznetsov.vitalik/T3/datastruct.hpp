#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <iostream>
#include <vector>

namespace kuznetsov
{
  struct Point
  {
    int x;
    int y;
  };

  std::istream& operator>>(std::istream& in, Point& point);

  struct Polygon
  {
    std::vector< Point > points;
  };

  std::istream& operator>>(std::istream& in, Polygon& polygon);

  struct Triangle
  {
    Point a;
    Point b;
    Point c;

    double getArea();
  };

  double getLength(const Point& a, const Point& b);
  double getAreaWithNextPoint(Triangle& triangle, const Point& newPoint);
  double getAreaPolygon(const Polygon& polygon);
  double getAreaEvenOrOdd(bool cur, double sum, const Polygon& polygon);
}

#endif

