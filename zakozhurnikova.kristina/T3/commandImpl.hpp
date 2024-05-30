#ifndef COMMAND_IMPL_HPP
#define COMMAND_IMPL_HPP

#include <functional>
#include <map>
#include <ostream>
#include <string>
#include "polygon.hpp"

namespace zakozhurnikova
{
  using Predicate = std::function< bool(const Polygon&) >;

  bool evenPredicate(const Polygon& polygon);
  bool oddPredicate(const Polygon& polygon);
  bool vertexNumPredicate(const Polygon& polygon, size_t vertexCount);
  double areaSum(double area, const Polygon& polygon);
  double getMeanArea(double area, const Polygon& polygon, size_t);
  double accumulateArea(const std::string& command, const std::vector< Polygon >& polygons);
  bool oddCountFunctor(const Polygon& polygon);
  bool evenCountFunctor(const Polygon& polygon);
  bool vertexesCountFunctor(const Polygon& polygon, size_t size);
  size_t countVertexes(const std::string& command, const std::vector< Polygon >& polygons);
  bool compareArea(const Polygon& lhs, const Polygon& rhs);
  bool compareVertex(const Polygon& lhs, const Polygon& rhs);
  void getMinArea(const std::vector< Polygon >& polygons, std::ostream& out);
  void getMaxArea(const std::vector< Polygon >& polygons, std::ostream& out);
  void getMinVertex(const std::vector< Polygon >& polygons, std::ostream& out);
  void getMaxVertex(const std::vector< Polygon >& polygons, std::ostream& out);
}

#endif
