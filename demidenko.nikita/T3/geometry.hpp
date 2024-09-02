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

  double getPolygonArea(const Polygon& polygon);
  double getTriangleArea(const Point& top, const std::pair< const Point&, const Point& > base);
  double getDistance(const Point& first, const Point& second);

  bool isRightPolygon(const Polygon& polygon);
  bool isRightTriangle(const Point& top, const std::pair< const Point&, const Point& > base);
  bool isPointEqual(const Point& first, const Point& second);
  bool isPolygonEqual(const Polygon& first, const Polygon& second);
}

#endif
