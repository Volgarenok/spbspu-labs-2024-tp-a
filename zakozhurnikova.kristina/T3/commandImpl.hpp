#ifndef COMMAND_IMPL_HPP
#define COMMAND_IMPL_HPP

#include <functional>
#include <map>
#include <ostream>
#include <string>
#include "polygon.hpp"

namespace zakozhurnikova
{

  struct PolygonAreaComputer
  {
    Point p1;
    double operator()(double area, const Point& p2, const Point& p3);
  };

  double getEvenOddArea(double area, const Polygon& polygon, bool isOdd);
  double getVertexesArea(double area, const Polygon& polygon, std::size_t size);
  double getMeanArea(double area, const Polygon& polygon, std::size_t);
  double accumulateArea(const std::string& command, const std::vector< Polygon >& polygons);
}

#endif
