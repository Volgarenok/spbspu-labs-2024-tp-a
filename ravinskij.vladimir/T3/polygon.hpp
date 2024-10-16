#ifndef POLYGON_HPP
#define POLYGON_HPP
#include <vector>
#include <ostream>

namespace ravinskij
{
  struct Point
  {
    int x;
    int y;
  };
  std::istream& operator>>(std::istream& in, Point& point);
  bool operator<(const Point& lhs, const Point& rhs);

  struct Polygon
  {
    std::vector< Point > points;
  };

  bool operator<=(const Polygon& lhs, const Polygon& rhs);
  bool isEmptyPolygon(const Polygon& polygon);
  double getArea(const Polygon& polygon);
  size_t polygonSize(const Polygon& polygon);
  int minX(const Polygon& polygon);
  int minY(const Polygon& polygon);
  int maxX(const Polygon& polygon);
  int maxY(const Polygon& polygon);

  Polygon getFrameRect(const std::vector < Polygon >& polygons);
  std::istream& operator>>(std::istream& in, Polygon& polygon);
}
#endif
