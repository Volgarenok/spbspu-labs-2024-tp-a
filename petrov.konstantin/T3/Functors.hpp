#ifndef FUNCS_HPP
#define FUNCS_HPP

#include "Geometry.hpp"

namespace petrov
{
  struct AccPolygonAreaPart
  {
    Point p1;
    double operator()(double area, const Point& p2, const Point& p3);
  };
  struct EqualPol
  {
    const Polygon& mask;
    bool operator()(const Polygon& p1, const Polygon& p2);
  };
}

#endif
