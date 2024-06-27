#ifndef AUXILIARYCOMMANDS_HPP
#define AUXILIARYCOMMANDS_HPP

#include "polygon.hpp"

namespace ayupov
{
  struct GetTriangleArea
  {
    Point one;
    Point two;
    double operator()(const Point&);
  };
  double calculatePolygonArea(const Polygon&);
  bool isOdd(const Polygon&);
  bool isEven(const Polygon&);
  bool isRightSize(const Polygon&, size_t);
}

#endif
