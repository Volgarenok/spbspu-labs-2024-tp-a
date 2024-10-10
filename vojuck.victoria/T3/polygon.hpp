#ifndef POLYGON_HPP
#define POLYGON_HPP
//RECTS INTERSECTIONS MAXSEQ

#include <vector>
#include <iostream>
#include <math.h>

namespace vojuck
{
  struct Point
  {
    int x;
    int y;
  };

  struct Polygon
  {
    std::vector< Point > points;
    double getArea() const;
    bool isRectangle() const;
  };
  std::istream &operator>>(std::istream&, Polygon&);

  void calculateArea(const std::vector< Polygon >&, const std::string&);
  void getMax(const std::vector< Polygon >&, const std::string&);
  void getMin(const std::vector< Polygon >&, const std::string&);
  void countPolygons(const std::vector< Polygon >&, const std::string&);
  void Rects(const std::vector< Polygon >&);
  double getDistance(const Point&, const Point&);
}

#endif
