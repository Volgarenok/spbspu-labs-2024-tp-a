#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <iostream>

namespace skuratov
{
  struct Point
  {
    int x, y;
  };
  std::istream& operator>>(std::istream& in, Point& point);
  std::ostream& operator<<(std::ostream& out, const Point& point);

  struct Polygon
  {
    std::vector< Point > points;
    double getArea() const;
  };
  std::istream& operator>>(std::istream& in, Polygon& polygon);
  std::ostream& operator<<(std::ostream & out, const Polygon & polygon);

  struct calculateArea
  {
    Point point1;
    double operator()(double acc, const Point& point2, const Point& point3);
  };
}

#endif
