#ifndef POLYGON_VERTICES_HPP
#define POLYGON_VERTICES_HPP

#include <vector>
#include <string>
#include <iostream>
#include "polygon.hpp"

namespace sivkov
{
  bool isEvenVertices(const Polygon& polygon);
  bool isOddVertices(const Polygon& polygon);
  double getOddEvenMean(std::vector< Polygon >& polygon, std::string arg);
  void maxVertex(std::ostream& out, const std::vector< Polygon >& polygons);
  void minVertex(std::ostream& out, const std::vector< Polygon >& polygons);
  size_t countVertex(const Polygon& polygon);
  bool hasVertexCount(const Polygon& polygon, size_t count);
}

#endif
