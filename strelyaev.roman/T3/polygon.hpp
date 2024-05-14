#ifndef POLYGON_HPP
#define POLYGON_HPP
#include <vector>
#include <iosfwd>

namespace strelyaev
{
  struct Point
  {
    int x;
    int y;
  };
  std::istream& operator>>(std::istream&, Point&);

  struct Polygon
  {
    std::vector< Point > points;
  };
}

#endif
