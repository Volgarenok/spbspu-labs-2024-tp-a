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
  };
  struct Polygon
  {
    std::vector< Point > points;
  };

  std::istream& operator>>(std::istream& in, Point& point);
  std::ostream& operator<<(std::ostream& in, const Point& point);
}
#endif
