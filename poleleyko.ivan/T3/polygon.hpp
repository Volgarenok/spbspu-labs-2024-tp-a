#ifndef POLYGON_HPP
#define POLYGON_HPP
#include <istream>
#include <vector>

namespace poleleyko
{
  struct Point
  {
    int x;
    int y;
  };
  std::istream & operator>>(std::istream & in, Point & point);

  struct Polygon
  {
    std::vector< Point > points;
  };
  std::istream & operator>>(std::istream & in, Polygon & polygon);
}

#endif