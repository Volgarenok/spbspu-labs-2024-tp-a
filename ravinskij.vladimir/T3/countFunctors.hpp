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
    std::size_t operator()(const std::string& subCommand);
  };

  struct EvenOddCountFunctor
  {
    bool operator()(const Polygon& polygon, bool isOdd);
  };

  struct VertexNumCountFunctor
  {
    bool operator()(const Polygon& polygon, std::size_t vertexCount);
  };
}
#endif
