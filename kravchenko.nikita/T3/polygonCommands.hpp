#ifndef POLYGON_COMMANDS_HPP
#define POLYGON_COMMANDS_HPP

#include <exception>
#include <iostream>
#include <vector>
#include "polygon.hpp"

namespace kravchenko
{
  void cmdArea(const std::vector< Polygon >& data, std::istream& in, std::ostream& out);
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

  void cmdMinMax(const std::vector< Polygon >& data, std::istream& in, std::ostream& out, bool isMin);
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

  void cmdCount(const std::vector< Polygon >& data, std::istream& in, std::ostream& out);

  void cmdRmEcho(std::vector< Polygon >& data, std::istream& in, std::ostream& out);

  void cmdRightShapes(const std::vector< Polygon >& data, std::ostream& out);
}

#endif
