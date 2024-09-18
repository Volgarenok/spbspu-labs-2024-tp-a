#ifndef AREA_FUNCTORS_HPP
#define AREA_FUNCTORS_HPP

#include <string>
#include <unordered_map>
#include <functional>
#include "polygon.hpp"

namespace ravinskij
{
  using Predicate = std::function< bool(const Polygon&) >;

  class AccumulateArea
  {
    using SubCommand = std::function< double(const Polygon&) >;
    using Filter = std::function< bool(const Polygon&) >;
  public:
    const std::vector< Polygon >& polygons;
    AccumulateArea(const std::vector< Polygon >& vector);
    double operator()(const std::string& subCommand);
  private:
    std::unordered_map< std::string, SubCommand > subCommands;
    std::unordered_map< std::string, Filter > filters;
    std::unordered_map< std::string, bool > emptyVectorSupport;
  };

  struct AreaSummator
  {
    double operator()(double area, const Polygon& polygon);
  };

  struct EvenPredicate
  {
    bool operator()(const Polygon& polygon);
  };

  struct MeanArea
  {
    double operator()(double area, const Polygon& polygon, size_t size);
  };

  struct VertexNumPredicate
  {
    bool operator()(const Polygon& polygon, size_t vertexCount);
  };
}

#endif
