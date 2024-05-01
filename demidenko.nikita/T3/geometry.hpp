#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <iosfwd>
#include <vector>

namespace demidenko
{
  struct Point
  {
    int x;
    int y;
  };
  struct Polygon
  {
    std::vector< Point > points;
  };

  std::istream& operator>>(std::istream& in, Point& point);
  std::istream& operator>>(std::istream& in, Polygon& polygon);
  std::ostream& operator<<(std::ostream& out, const Point& point);
  std::ostream& operator<<(std::ostream& out, const Polygon& polygon);

  std::istream& readPolygons(std::istream& in, std::vector< Polygon >& polygons);

  double polygonArea(const Polygon& polygon);
  bool isRightPolygon(const Polygon& polygon);
  double triangleArea(const Point& top, const std::pair< Point, Point >& base);
  bool isRightTriangle(const Point& top, const std::pair< Point, Point >& base);
  double distance(const Point& first, const Point& second);
}

#endif
