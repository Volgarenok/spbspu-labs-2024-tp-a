#ifndef COUNT_FUNCTORS_HPP
#define COUNT_FUNCTORS_HPP

#include <string>
#include <unordered_map>
#include <functional>
#include "polygon.hpp"

namespace ravinskij
{
  struct GetCount
  {
    using SubCommand = std::function < bool (const Polygon&) >;
    const std::vector< Polygon >& polygons;
    std::unordered_map< std::string, SubCommand > subCommands;
    GetCount(const std::vector< Polygon >& vector);
    size_t operator()(const std::string& subCommand);
  };

  struct EvenCountFunctor
  {
    bool operator()(const Polygon& polygon);
  };

  struct VertexNumCountFunctor
  {
    bool operator()(const Polygon& polygon, size_t vertexCount);
  };
}
#endif
