#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <vector>
#include <iomanip>

namespace serter
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

  bool operator==(const Point& lhs, const Point& rhs);

  std::istream& operator>>(std::istream& in, Point& dest);
  std::istream& operator>>(std::istream& in, Polygon& dest);
}

#endif

