#ifndef POLYGON_FUNCTORS_HPP
#define POLYGON_FUNCTORS_HPP

#include "Polygon.hpp"
#include "Point.hpp"

namespace sazanov
{
  struct AccumulatePolygonAreaPart
  {
    Point first;
    double operator()(double area, const Point& second);
  };
}
#endif
