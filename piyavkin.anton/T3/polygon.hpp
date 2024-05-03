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
    bool operator<(const Point& rhs) const;
  };
  std::istream& operator>>(std::istream& in, Point& p);
  using c_it_t = std::vector< Point >::const_iterator;
  struct Polygon
  {
    double getArea() const;
    std::vector< Point > points;
  private:
    double getAreaImpl(double curr, c_it_t it, c_it_t it2) const;
  };
  std::istream& operator>>(std::istream& in, Polygon& pol);
}
#endif