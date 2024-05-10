#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <istream>

namespace skuratov
{
  struct Point
  {
    int x, y;
  };
  std::istream& operator>>(std::istream& in, Point& point);

  struct Polygon
  {
    std::vector< Point > points;
  };
  std::istream& operator>>(std::istream& in, Polygon& polygon);
}

#endif
