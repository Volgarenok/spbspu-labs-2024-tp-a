#ifndef POLYGON_HPP
#define POLYGON_HPP
#include <vector>
#include <ostream>

namespace zakozhurnikova
{
  struct Point
  {
    int x;
    int y;
  };
  std::istream& operator>>(std::istream& in, Point& point);

  struct Polygon
  {
    std::vector< Point > points;
     double getArea() const;
  };
  std::istream& operator>>(std::istream& in, Polygon& polygon);
}

#endif
