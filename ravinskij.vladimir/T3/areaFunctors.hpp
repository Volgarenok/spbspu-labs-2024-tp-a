#ifndef AREA_FUNCTORS_HPP
#define AREA_FUNCTORS_HPP

#include <string>
#include <unordered_map>
#include <functional>
#include "polygon.hpp"

namespace ravinskij
{
  struct AccumulateArea
  {
    using SubCommand = std::function< double(double, const Polygon&) >;
    const std::vector< Polygon >& polygons;
    std::unordered_map< std::string, SubCommand > subCommands;
    std::unordered_map< std::string, bool > emptyVectorSupport;
    AccumulateArea(const std::vector< Polygon >& vector);
    double operator()(const std::string& subCommand);
  };

  struct EvenOddAreaFunctor
  {
    double operator()(double area, const Polygon& polygon, bool isOdd);
  };

  struct MeanArea
  {
    double operator()(double area, const Polygon& polygon, std::size_t size);
  };

  struct VertexNumArea
  {
    double operator()(double area, const Polygon& polygon, std::size_t vertexCount);
  };
}

#endif
