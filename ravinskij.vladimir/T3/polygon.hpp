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
  };
  std::istream& operator>>(std::istream& in, Point& point);
  std::ostream& operator<<(std::ostream& in, const Point& point);

  struct Polygon
  {
    std::vector< Point > points;
    bool operator==(const Polygon& rhs) const;
    bool empty() const;
    double getArea() const;
  };
  std::istream& operator>>(std::istream& in, Polygon& polygon);
  std::ostream& operator<<(std::ostream& out, const Polygon& polygon);
}
#endif
