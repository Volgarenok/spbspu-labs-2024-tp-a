#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <iostream>
#include <vector>

namespace basko
{
  struct Point
  {
    int x;
    int y;
  };
  std::istream& operator>>(std::istream& in, Point& point);
  bool operator==(const Point& lhs, const Point& rhs);

  struct Polygon
  {
    std::vector< Point > points;
  };
  double getPolygonArea(const Polygon& polygon);
  std::istream& operator>>(std::istream& in, Polygon& polygon);
  bool operator==(const Polygon& lhs, const Polygon& rhs);
  bool operator<=(const Polygon& lhs, const Polygon& rhs);
  bool isRightAngle(const Polygon& polygon);
  int findMaxX(const Polygon& polygon);
  int findMaxY(const Polygon& polygon);
  int findMinX(const Polygon& polygon);
  int findMinY(const Polygon& polygon);
  Polygon getBoundingBox(const std::vector< Polygon >& polygon);

  struct AreaPolygon
  {
    Point p1;
    double operator()(double area, const Point& p2, const Point& p3);
  };

  struct accumulateRightAngle
  {
    Point p1;
    Point p2;
    bool operator()(const Point& p3);
  };
}

#endif
