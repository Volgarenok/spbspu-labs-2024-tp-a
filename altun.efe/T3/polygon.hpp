#ifndef POLYGON_HPP
#define POLYGON_HPP
#include <iosfwd>
#include <vector>

namespace altun
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

  std::istream& operator>>(std::istream&, Polygon&);
  bool operator==(const Polygon&, const Polygon&);
  bool operator==(const Point&, const Point &);

  size_t getSize(const Polygon&);
  int getX(const Point&);
  int getY(const Point&);
  double getPolyArea(const Polygon&);
}

#endif
