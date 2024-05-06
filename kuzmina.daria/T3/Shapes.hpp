#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <iostream>
#include <vector>

namespace kuzmina
{
  struct Point
  {
    int x, y;
    bool operator==(const Point&) const;
  };

  struct Polygon
  {
    std::vector< Point > points;
    double getArea() const;
    int countRightAngles() const;
  };

  struct CountArea
  {
    Point point1;
    double operator()(double, const Point&, const Point&);
  };

  struct CountAngle
  {
    Point point1, point2;
    bool operator()(const Point&);
  };

  std::istream& operator>>(std::istream&, Point&);
  std::ostream& operator<<(std::ostream&, const Point&);

  std::istream& operator>>(std::istream&, Polygon&);
  std::ostream& operator<<(std::ostream&, const Polygon&);
}

#endif
