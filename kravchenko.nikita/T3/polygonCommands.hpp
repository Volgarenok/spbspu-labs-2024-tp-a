#ifndef POLYGON_COMMANDS_HPP
#define POLYGON_COMMANDS_HPP

#include <exception>
#include <iostream>
#include <vector>
#include "polygon.hpp"

namespace kravchenko
{
  class InvalidCommand: public std::exception
  {
  public:
    const char* what() const noexcept override;
  };

  struct CmdStreams
  {
    std::istream& in;
    std::ostream& out;
  };

  struct Area
  {
    void operator()(const std::vector< Polygon >& data, CmdStreams args);
  };
  struct AccumulateAreaParity
  {
    double operator()(double acc, const Polygon& p, bool isEven);
  };
  struct AccumulateAreaMean
  {
    std::size_t numOfPolygons;
    double operator()(double acc, const Polygon& p);
  };
  struct AccumulateAreaNumOfVertex
  {
    double operator()(double acc, const Polygon& p, std::size_t numOfVertexes);
  };

  struct MinMax
  {
    void operator()(const std::vector< Polygon >& data, CmdStreams args, bool isMin);
  };
  struct AccumulateMinMaxArea
  {
    double operator()(double acc, const Polygon& p, bool isMin);
  };
  struct AccumulateMinMaxVertexes
  {
    std::size_t operator()(std::size_t acc, const Polygon& p, bool isMin);
  };

  struct Count
  {
    void operator()(const std::vector< Polygon >& data, CmdStreams args);
  };
  struct ParityPred
  {
    bool operator()(const Polygon& p, bool isEven);
  };
  struct NumOfVertexPred
  {
    bool operator()(const Polygon& p, std::size_t numOfVertexes);
  };

  struct RmEcho
  {
    void operator()(std::vector< Polygon >& data, CmdStreams args);
  };
  struct ConsecutiveIdenticalPolygonPred
  {
    bool operator()(const Polygon& p1, const Polygon& p2, const Polygon& compared);
  };

  struct RightShapes
  {
    void operator()(const std::vector< Polygon >& data, CmdStreams args);
  };
  struct RightPolygonsPred
  {
    bool operator()(const Polygon& p);
  };
}

#endif
