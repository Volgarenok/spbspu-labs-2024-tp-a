#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <iostream>
#include <vector>


namespace sivkov
{
  struct Point
  {
    int x;
    int y;
  };

  bool operator<(const Point& point1, const Point& point2);
  bool operator==(const Point& point1, const Point& point2);
  std::istream& operator>>(std::istream& in, Point& value);

  struct Polygon
  {
    std::vector< Point > points;
  };

  bool operator==(const Polygon& polygon1, const Polygon& polygon2);
  std::istream& operator>>(std::istream& in, Polygon& value);

  double calculatePolygonAreaHelper(const std::vector<Point>& points, size_t j, size_t i, double area);
  double calculatePolygonArea(const Polygon& polygon);
}
#endif
