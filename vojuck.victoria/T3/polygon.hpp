#ifndef POLYGON_HPP
#define POLYGON_HPP
//RECTS INTERSECTIONS MAXSEQ

#include <vector>

namespace vojuck
{
  struct Point
  {
    int x;
    int y;
  };

  std::istream &operator>>(std::istream&, Point&);

  struct Polygon
  {
    std::vector< Point > points;
    double getArea();
  };
  std::istream &operator>>(std::istream&, Polygon&);

  void printArea(const std::vector<Polygon>&, const std::string&);
}

#endif
