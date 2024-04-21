#ifndef POLYGON_COMMANDS_HPP
#define POLYGON_COMMANDS_HPP

#include <iostream>
#include <vector>
#include "polygon.hpp"

namespace kravchenko
{
  struct Area
  {
    void operator()(std::vector< Polygon >& data, std::istream& in, std::ostream& out);
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
    void operator()(std::vector< Polygon >& data, std::istream& in, std::ostream& out, bool isMin);
  };
  struct AccumulateMinMaxArea
  {
    double operator()(double acc, const Polygon& p, bool isMin);
  };
  struct AccumulateMinMaxVertexes
  {
    std::size_t operator()(std::size_t acc, const Polygon& p, bool isMin);
  };
}

#endif