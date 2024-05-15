#ifndef SHAPES_HPP
#define SHAPES_HPP
#include <functional>
#include <iostream>
#include <vector>

namespace babinov
{
  struct Point
  {
    int x, y;
  };
  std::istream& operator>>(std::istream& in, Point& point);

  struct Polygon
  {
    std::vector< Point > points;
  };
  std::istream& operator>>(std::istream& in, Polygon& polygon);

  struct Vector
  {
    Point coords;
    Vector(const Point& begin, const Point& end);
    double operator*(const Vector& other) const;
    double getLength() const;
    double findCosBetween(const Vector& other) const;
  };

  struct Triangle
  {
    Point a, b, c;
  };

  double getArea(const Polygon& polygon);
  size_t getVertexes(const Polygon& polygon);
  bool isRectangle(const Polygon& polygon);
  bool isIntersect(const Polygon& first, const Polygon& second);
}

#endif
