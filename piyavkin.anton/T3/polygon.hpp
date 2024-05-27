#ifndef POLYGON_HPP
#define POLYGON_HPP
#include <vector>
#include <algorithm>
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
  struct Polygon
  {
    std::vector< Point > points;
  };
  std::istream& operator>>(std::istream& in, Polygon& pol);
  double getAreaPol(const Polygon& pol);
  double getArea(const std::vector< Polygon >& pols);
  template< class F >
  double getCorArea(const std::vector< Polygon >& pols, F f)
  {
    std::vector< Polygon > correctPols;
    std::copy_if(pols.cbegin(), pols.cend(), std::back_inserter(correctPols), f);
    return getArea(correctPols);
  }
}
#endif
