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

  void cmdArea(const std::vector< Polygon >& data, CmdStreams args);
  namespace area
  {
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
      std::size_t numOfVertexes;
      double operator()(double acc, const Polygon& p);
    };
  }

  void cmdMinMax(const std::vector< Polygon >& data, CmdStreams args, bool isMin);
  namespace minMax
  {
    struct AccumulateMinMaxArea
    {
      double operator()(double acc, const Polygon& p, bool isMin);
    };
    struct AccumulateMinMaxVertexes
    {
      std::size_t operator()(std::size_t acc, const Polygon& p, bool isMin);
    };
  }

  void cmdCount(const std::vector< Polygon >& data, CmdStreams args);
  namespace count
  {
    struct ParityPred
    {
      bool operator()(const Polygon& p, bool isEven);
    };
    struct NumOfVertexPred
    {
      std::size_t numOfVertexes;
      bool operator()(const Polygon& p);
    };
  }

  void cmdRmEcho(std::vector< Polygon >& data, CmdStreams args);

  void cmdRightShapes(const std::vector< Polygon >& data, CmdStreams args);
}

#endif
