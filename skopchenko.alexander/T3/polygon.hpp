#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <iostream>
#include <vector>

namespace skopchenko
{
  struct Point
  {
    int x;
    int y;
  };
  bool operator==(const Point& first, const Point& second);
  bool operator<(const Point& first, const Point& second);
  bool operator<=(const Point& first, const Point& second);
  bool operator>=(const Point& first, const Point& second);
  std::istream& operator>>(std::istream& in, Point& point);
  struct Polygon
  {
    std::vector< Point > points;
  };
  double getPolygonArea(const Polygon& polygon);
  bool operator==(const Polygon& first, const Polygon& second);
  std::istream& operator>>(std::istream& in, Polygon& polygon);
}

#endif
