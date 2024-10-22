#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include <ostream>
#include "polygon.hpp"

namespace agarkov
{
  void getAreaEven(const std::vector< Polygon >& polygons, std::ostream& out);
  void getAreaOdd(const std::vector< Polygon >& polygons, std::ostream& out);
  void getAreaMean(const std::vector< Polygon >& polygons, std::ostream& out);
  void getAreaVertexes(const std::vector< Polygon >& polygons, size_t count, std::ostream& out);
  void getMaxArea(const std::vector< Polygon >& polygons, std::ostream& out);
  void getMaxVertexes(const std::vector< Polygon >& polygons, std::ostream& out);
  void getMinArea(const std::vector< Polygon >& polygons, std::ostream& out);
  void getMinVertexes(const std::vector< Polygon >& polygons, std::ostream& out);
  void getCountEven(const std::vector< Polygon >& polygons, std::ostream& out);
  void getCountOdd(const std::vector< Polygon >& polygons, std::ostream& out);
  void getCountVertexes(const std::vector< Polygon >& polygons, size_t count, std::ostream& out);
  void getSame(const std::vector< Polygon >& polygons, const Polygon& polygon, std::ostream& out);
  void getRects(const std::vector< Polygon >& polygons, std::ostream& out);
  void getMaxSequence(const std::vector< Polygon >& polygons, const Polygon& polygon, std::ostream& out);
}

#endif
