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
  size_t getSize(const Polygon&);
  int getX(const Point&);
  int getY(const Point&);
  double getArea(const Polygon&);
  bool operator==(const Polygon&, const Polygon&);
  bool operator==(const Point&, const Point&);

}

#endif
