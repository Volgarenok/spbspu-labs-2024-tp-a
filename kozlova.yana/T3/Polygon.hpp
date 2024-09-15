#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <istream>
#include <algorithm>

namespace kozlova
{
  struct Point
  {
    int x, y;
  };
  std::istream& operator>>(std::istream& in, Point& point);
  bool operator==(const Point& point1, const Point& point2);

  struct Polygon
  {
    std::vector< Point > points;
  };

  std::istream& operator>>(std::istream& in, Polygon& polygon);
  bool operator==(const Polygon& polygon1, const Polygon& polygon2);
  double getAreaPolygon(const Polygon& polygon);
  double getAreaPolygons(const std::vector< Polygon >& polygons);
}

#endif
