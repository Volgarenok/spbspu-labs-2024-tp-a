#ifndef AREA_HPP
#define AREA_HPP

#include "geometry.hpp"
namespace demidenko
{
  struct Triangle
  {
    Point first;
    Point second;
    Point third;
    double area() const;
  };
  Triangle buildTriangle(const std::pair< Point, Point >& base, const Point& top);
  double polygonArea(const Polygon& polygon);
  double distance(const Point& first, const Point& second);
}

#endif
