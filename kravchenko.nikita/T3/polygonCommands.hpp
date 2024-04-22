#ifndef POLYGON_COMMANDS_HPP
#define POLYGON_COMMANDS_HPP

#include <iostream>
#include <vector>
#include "polygon.hpp"
#include "polygonHandler.hpp"

namespace kravchenko
{
  struct Area
  {
    void operator()(CommandArguments args);
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
    void operator()(CommandArguments args, bool isMin);
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
    void operator()(CommandArguments args);
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
    void operator()(CommandArguments args);
  };
  struct ConsecutiveIdenticalPolygonPred
  {
    bool operator()(const Polygon& p1, const Polygon& p2, const Polygon& compared);
  };

  struct RightShapes
  {
    void operator()(CommandArguments args);
  };
  struct RightPolygonsPred
  {
    bool operator()(const Polygon& p);
  };
}

#endif
