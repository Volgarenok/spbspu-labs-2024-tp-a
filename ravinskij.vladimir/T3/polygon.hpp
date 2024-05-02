#ifndef POLYGON_HPP
#define POLYGON_HPP
#include <vector>
#include <ostream>
#include <delimeters.hpp>
namespace ravinskij
{
  struct Point
  {
    int x;
    int y;
    bool operator==(const Point& rhs) const;
    bool operator<(const Point& rhs) const;
    bool operator<=(const Point& rhs) const;
    bool operator>=(const Point& rhs) const;
  };
  std::istream& operator>>(std::istream& in, Point& point);

  struct Polygon
  {
    std::vector< Point > points;
    bool operator==(const Polygon& rhs) const;
    bool operator<=(const Polygon& rhs) const;
    bool empty() const;
    double getArea() const;
    std::size_t size() const;
    int minX() const;
    int minY() const;
    int maxX() const;
    int maxY() const;
  };
  Polygon getFrameRect(const std::vector < Polygon >& polygons);
  std::istream& operator>>(std::istream& in, Polygon& polygon);
}
#endif
