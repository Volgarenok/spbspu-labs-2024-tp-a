#ifndef POLYGON_COMMANDS_HPP
#define POLYGON_COMMANDS_HPP
#include <exception>
#include <iostream>
#include <vector>
#include "polygon.hpp"

namespace spiridonov
{
  class InvalidActionException: public std::exception
  {
  public:
    const char* what() const noexcept override;
  };

  struct ActionStreams
  {
    std::istream& in;
    std::ostream& out;
  };

  void areaAction(const std::vector< Polygon >& polygons, ActionStreams args);

  struct AccumulateAreaParity
  {
    double operator()(double acc, const Polygon& polygon, bool isEven);
  };

  struct AccumulateAreaMean
  {
    std::size_t numberOfPolygons;
    double operator()(double acc, const Polygon& polygon);
  };

  struct AccumulateAreaNumOfVertex
  {
    std::size_t numberOfVertices;
    double operator()(double acc, const Polygon& polygon);
  };

  void minMaxAction(const std::vector< Polygon >& polygons, ActionStreams args, bool isMin);

  struct AccumulateMinMaxArea
  {
    double operator()(double acc, const Polygon& polygon, bool isMin);
  };

  struct AccumulateMinMaxVertexes
  {
    std::size_t operator()(std::size_t acc, const Polygon& polygon, bool isMin);
  };

  void countAction(const std::vector< Polygon >& polygons, ActionStreams args);

  struct ParityPred
  {
    bool operator()(const Polygon& polygon, bool isEven);
  };

  struct NumOfVertexPred
  {
    std::size_t numberOfVertices;
    bool operator()(const Polygon& polygon);
  };

  void echoAction(std::vector< Polygon >& polygons, ActionStreams args);

  void lessAreaAction(std::vector< Polygon >& polygon, ActionStreams args);
}

#endif
