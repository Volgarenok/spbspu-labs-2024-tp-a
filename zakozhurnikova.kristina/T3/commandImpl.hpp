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
  bool evenOddCountFunctor(const Polygon& polygon, bool isOdd);
  bool vertexesCountFunctor(const Polygon& polygon, std::size_t size);
  std::size_t countVertexes(const std::string& command, const std::vector< Polygon >& polygons);
  bool compareArea(const Polygon& lhs, const Polygon& rhs);
  bool compareVertex(const Polygon& lhs, const Polygon& rhs);
  void getMinArea(const std::vector< Polygon >& polygons, std::ostream& out);
  void getMaxArea(const std::vector< Polygon >& polygons, std::ostream& out);
  void getMinVertex(const std::vector< Polygon >& polygons, std::ostream& out);
  void getMaxVertex(const std::vector< Polygon >& polygons, std::ostream& out);
}

#endif
