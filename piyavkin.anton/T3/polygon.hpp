#ifndef POLYGON_HPP
#define POLYGON_HPP
#include <vector>
#include <istream>
#include <ostream>

namespace piyavkin
{
  struct Point
  {
    int x;
    int y;
  };
  std::istream& operator>>(std::istream& in, Point& p);
  
  struct Polygon
  {
    std::vector< Point > points;
  };
  std::istream& operator>>(std::istream& in, Polygon& pol);
}
#endif