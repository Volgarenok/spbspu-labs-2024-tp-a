#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include "Geometry.hpp"
#include "Utils.hpp"

namespace petrov
{
  double getAreaEO(const std::vector< Polygon >& polygons, bool isEven);
  double getAreaAverage(const std::vector< Polygon >& polygons);
  double getAreaNumOfVertexes(const std::vector< Polygon >& polygons, size_t numOfVertexes);
  double getExtremum(const std::vector< Polygon >& polygons, bool forArea, bool forMax);
  size_t countEON(const std::vector< Polygon >& polygons, bool isEven);
  size_t countEON(const std::vector< Polygon >& polygons, double numOfVertexes);
  double rmEcho(std::vector< Polygon >& polygons, const Polygon& mask);
  double countSame(const std::vector< Polygon >& polygons, const Polygon& mask);
}

#endif
