#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include "Geometry.hpp"
#include "Utils.hpp"

namespace petrov
{
  double getAreaEO(const std::vector< Polygon >& polygons, bool forEven);
  double getAreaAverage(const std::vector< Polygon >& polygons);
  double getAreaNumOfVertexes(const std::vector< Polygon >& polygons, size_t numOfVertexes);
  double getExtremum(const std::vector< Polygon >& polygons, bool forArea, bool forMax);
  double countPolygonsEO(const std::vector< Polygon >& polygons, bool forEven);
  double countPolygonsNumOfVertexes(const std::vector< Polygon >& Polygons, size_t numOfVertexes);
  double rmEcho(std::vector< Polygon >& polygons, const Polygon& mask);
  double countSame(const std::vector< Polygon >& polygons, const Polygon& mask);
}

#endif
