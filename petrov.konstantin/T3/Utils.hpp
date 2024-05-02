#ifndef UTILS_HPP
#define UTILS_HPP

#include "Geometry.hpp"

namespace petrov
{
  struct AccPolygonAreaPart
  {
    Point p1;
    double operator()(double area, const Point& p2, const Point& p3);
  };

  double AccPolygonAreaEO(double area, const Polygon& polygon, bool isEven);
  double AccPolygonArea(double area, const Polygon& polygon);
  double AccPolygonAreaNumOfVertexes(double area, const Polygon& polygon, size_t numOfVertexes);
  double AccPolygonMax(double max, const Polygon& polygon, bool forArea);
  double AccPolygonMin(double min, const Polygon& polygon, bool forArea);
  size_t AccPolygonEON(size_t counter, const Polygon& polygon, bool isEven);
  size_t AccPolygonEON(size_t counter, const Polygon& polygon, size_t numOfVertexes);

}

#endif 