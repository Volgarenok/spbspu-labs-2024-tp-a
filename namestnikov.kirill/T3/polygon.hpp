#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <iostream>
#include <vector>

namespace namestnikov
{
  struct Point
  {
    int x;
    int y;
    bool operator==(const Point & other) const;
    bool operator<(const Point & other) const;
    bool operator>(const Point & other) const;
    bool operator<=(const Point & other) const;
    bool operator>=(const Point & other) const;
  };
  std::istream & operator>>(std::istream & in, Point & point);
  std::ostream & operator<<(std::ostream & out, const Point & point);

  struct Polygon
  {
    std::vector< Point > points;
  };
  double getPolygonArea(const Polygon & polygon);
  bool operator==(const Polygon & first, const Polygon & second);
  std::istream & operator>>(std::istream & in, Polygon & polygon);
  std::ostream & operator<<(std::ostream & out, const Polygon & polygon);

  struct PolygonArea
  {
    Point first;
    double operator()(double area, const Point & second, const Point & third);
  };
}

#endif
