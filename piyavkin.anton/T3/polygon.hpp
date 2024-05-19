#ifndef POLYGON_HPP
#define POLYGON_HPP
#include <vector>
#include <istream>

namespace piyavkin
{
  struct Point
  {
    int x;
    int y;
  };
  bool operator<(const Point& lhs, const Point& rhs);
  std::istream& operator>>(std::istream& in, Point& p);
  using c_it_t = std::vector< Point >::const_iterator;
  struct Polygon
  {
    std::vector< Point > points;
  };
  std::istream& operator>>(std::istream& in, Polygon& pol);
  double getArea(const Polygon& pol);
  namespace detail
  {
    struct calculateArea
    {
      Point changP;
      double operator()(const Point& p1, const Point& p2);
    };
    
  }
}
#endif
