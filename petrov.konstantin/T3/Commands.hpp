#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include "Geometry.hpp"

namespace petrov
{
  enum EON
  {
    EVEN,
    ODD,
    NUM_OF_VERTEXES
  };

  double getAreaEO(const std::vector< Polygon >& polygons, bool isEven);
  double getAreaAverage(const std::vector< Polygon >& polygons);
  double getAreaNumOfVertexes(const std::vector< Polygon >& polygons, size_t numOfVertexes);
  double getAreaMax(const std::vector< Polygon >& polygons, bool forArea);
  double getAreaMin(const std::vector< Polygon >& polygons, bool forArea);
  double countEON(const std::vector< Polygon >& polygons, EON setting);
  double rmEcho(std::vector< Polygon >& polygons, const Polygon& mask);
  double countSame(const std::vector< Polygon >& polygons, const Polygon& mask);
}

#endif
