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
  bool operator==(const Point& lhs, const Point& rhs);
  bool operator<(const Point& lhs, const Point& rhs);
  bool operator<=(const Point& lhs, const Point& rhs);
  bool operator>=(const Point& lhs, const Point& rhs);

  struct Polygon
  {
    std::vector< Point > points;
    bool operator==(const Polygon& rhs) const;
    bool operator<=(const Polygon& rhs) const;
    bool empty() const;
    double getArea() const;
    size_t size() const;
    int minX() const;
    int minY() const;
    int maxX() const;
    int maxY() const;
  };
  Polygon getFrameRect(const std::vector < Polygon >& polygons);
  std::istream& operator>>(std::istream& in, Polygon& polygon);
}
#endif
