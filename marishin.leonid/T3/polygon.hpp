#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <iostream>
#include <vector>

namespace marishin
{
  struct Point
  {
    int x, y;
  };
  bool operator==(const Point& first, const Point& second);
  bool operator>=(const Point& first, const Point& second);
  bool operator<=(const Point& first, const Point& second);
  bool operator<(const Point& first, const Point& second);
  std::istream& operator>>(std::istream& in, Point& point);
  std::ostream& operator<<(std::ostream& out, const Point& point);
  struct Polygon
  {
    std::vector< Point > points;
    double getArea() const;
  };
  std::istream& operator>>(std::istream& in, Polygon& point);
  std::ostream& operator<<(std::ostream& out, const Polygon& point);
  bool operator==(const Polygon& first, const Polygon& second);

  struct PolygonArea
  {
    Point first;
    double operator()(double area, const Point& second, const Point& third);
  };

  struct RectangleVector
  {
    Point vertexes;
    RectangleVector(const Point& p1, const Point& p2);
    double operator*(const RectangleVector& p1);
    double getLength() const;
    double cos(const RectangleVector& p1);
  };
}

#endif
