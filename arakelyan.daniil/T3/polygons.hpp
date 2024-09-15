#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <iosfwd>
#include <vector>

namespace arakelyan
{
  struct Point
  {
    int x_;
    int y_;
  };

  std::istream &operator>>(std::istream&, Point&);

  struct Polygon
  {
    std::vector< Point > points;
  };

  std::istream &operator>>(std::istream&, Polygon&);
  size_t get_size(const Polygon&);
  int get_x(const Point&);
  int get_y(const Point&);
  double get_area(const Polygon&);
  bool operator==(const Polygon&, const Polygon&);
  bool operator==(const Point&, const Point&);

}

#endif
