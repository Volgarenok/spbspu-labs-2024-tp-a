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
    bool operator==(const Point& other) const;
  };
  std::istream& operator>>(std::istream& in, Point& p);
  std::ostream& operator<<(std::ostream& out, const Point& p);

  struct Polygon
  {
    std::vector< Point > points;
    double getArea() const;
    bool isIdentical(const Polygon& other) const;
    bool hasRightAngle() const;
  };
  std::istream& operator>>(std::istream& in, Polygon& p);
  std::ostream& operator<<(std::ostream& out, const Polygon& p);

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
