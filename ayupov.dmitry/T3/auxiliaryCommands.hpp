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
  size_t vertexesNumber(const Polygon&);
  double maxArea(const std::vector<Polygon>);
  double minArea(const std::vector<Polygon>);
  size_t maxVertexes(const std::vector<Polygon>);
  size_t minVertexes(const std::vector<Polygon>);
}

#endif
