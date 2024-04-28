#ifndef POLYGON_FUNCTORS_HPP
#define POLYGON_FUNCTORS_HPP

#include "Polygon.hpp"
#include "Point.hpp"

namespace sazanov
{
  struct AccumulatePolygonAreaPart
  {
    Point p1;
    double operator()(double area, const Point& p2, const Point& p3);
  };
}

#endif
