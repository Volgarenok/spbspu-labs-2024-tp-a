#ifndef POLYGON_HPP
#define POLYGON_HPP
#include <iostream>
#include <vector>
#include <numeric>

namespace kozakova
{
  struct Point
  {
    int x;
    int y;
    bool operator<(const Point& p) const;
    bool operator==(const Point& p) const;
  };
  std::istream& operator>>(std::istream& in, Point& value);


  struct Polygon
  {
    std::vector< Point > points;
    double getArea() const;
    bool isRect();
    bool operator==(const Polygon& p) const;
  };
  std::istream& operator>>(std::istream& in, Polygon& value);

  struct PolygonArea
  {
    Point first;
    double operator()(double area, const Point& second);
  };
}
#endif
