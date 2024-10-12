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
    bool operator==(const Point&) const;
  };

  struct Polygon
  {
    std::vector< Point > points;
    double getArea() const;
    bool isRectangle() const;
    bool operator==(const Polygon&) const;
  };
  std::istream &operator>>(std::istream&, Polygon&);

  void calculateArea(const std::vector< Polygon >&, const std::string&);
  void getMax(const std::vector< Polygon >&, const std::string&);
  void getMin(const std::vector< Polygon >&, const std::string&);
  void countPolygons(const std::vector< Polygon >&, const std::string&);
  void rects(const std::vector< Polygon >&);
  double getDistance(const Point&, const Point&);
  void maxSeq(const std::vector< Polygon >&, std::istream&);
  double triangleArea(const Point&, const Point&, const Point&);
  bool doLineSegmentsIntersect(const Point&, const Point&, const Point&, const Point&);
  bool doPolygonsIntersect(const Polygon&, const Polygon&);
  void intersections(const std::vector< Polygon>&, std::istream&);
}

#endif
