#ifndef AUXILIARYCOMMANDS_HPP
#define AUXILIARYCOMMANDS_HPP

#include "polygon.hpp"

namespace ayupov
{
  struct getTriangleArea
  {
    Point one;
    Point two;
    double operator()(const Point&);
  };
  bool isOdd(Polygon&);
  bool isEven(Polygon&);
}

#endif
