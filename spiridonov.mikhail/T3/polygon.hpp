#ifndef POLYGON_HPP
#define POLYGON_HPP
#include <iostream>
#include <vector>

namespace spiridonov
{
  struct Point
  {
    int x;
    int y;
    bool operator==(const Point& other) const;
  };
  std::istream& operator>>(std::istream& in, Point& point);
  std::ostream& operator<<(std::ostream& out, const Point& point);

  struct Polygon
  {
    std::vector< Point > points;
    double getArea() const;
    bool isIdentical(const Polygon& other) const;
    bool isLessArea(const Polygon& other) const;
  };
  std::istream& operator>>(std::istream& in, Polygon& polygon);
  std::ostream& operator<<(std::ostream& out, const Polygon& polygon);

  struct AccumulatePolygonArea
  {
    Point point1;
    double operator()(double acc, const Point& point2, const Point& point3);
  };
}

#endif
