#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <vector>
#include <iostream>

namespace artemev
{
  struct Point
  {
    int x, y;
    bool operator==(const Point& oth) const;
  };
  std::istream& operator>>(std::istream& in, Point& point);

  struct Polygon
  {
    std::vector< Point > points;
    double getArea() const;
    int countRightAngle() const;
  };
  std::istream& operator>>(std::istream& in, Polygon& polygon);

  struct AccumulateArea
  {
    Point first;
    double operator()(double area, const Point& second, const Point& third);
  };

  struct AccumulateAngle
  {
    Point first, second;
    bool operator()(const Point& third);
  };
}

#endif
