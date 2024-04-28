#ifndef SHAPES_HPP
#define SHAPES_HPP
#include <iostream>
#include <vector>

namespace babinov
{
  struct Point
  {
    int x, y;
    Point& operator=(const Point& other);
  };
  std::istream& operator>>(std::istream& in, Point& point);

  struct Polygon
  {
    std::vector< Point > points;
  };
  std::istream& operator>>(std::istream& in, Polygon& polygon);

  struct Vector
  {
    Vector(const Point& begin, const Point& end);
    Point coords;
    double operator*(const Vector& other) const;
    double getLength() const;
    double findCosBetween(const Vector& other) const;
  };

  struct Triangle
  {
    Point a, b, c;
  };
}

#endif
