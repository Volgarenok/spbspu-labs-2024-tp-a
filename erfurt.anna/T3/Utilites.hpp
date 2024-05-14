#ifndef UTILITES_HPP
#define UTILITES_HPP

#include "Polygon.hpp"

namespace erfurt
{
  struct AccAreaEvenOdd
  {
    double operator()(double sum, const Polygon & poly);
    std::string parameter;
  };

  struct AccAreaMean
  {
    double operator()(double sum, const Polygon & poly);
    size_t count;
  };

  struct AccAreaVertexes
  {
    double operator()(double sum, const Polygon & poly);
    int numOfVertexes;
  };

  bool isPerm(const Polygon& poly1, const Polygon & poly2);

  struct IdenticalPoly
  {
    bool operator()(const Polygon & p1, const Polygon & p2);
    Polygon& poly;
  };

  struct AccumulatePolygonArea
  {
    Point p0;
    double operator()(double area, const Point & p1, const Point & p2);
  };
}

#endif
