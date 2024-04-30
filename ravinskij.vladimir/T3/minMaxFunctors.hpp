#ifndef MIN_MAX_FUNCTORS_HPP
#define MIN_MAX_FUNCTORS_HPP

#include <string>
#include <functional>
#include <unordered_map>
#include <utility>
#include <ostream>
#include "polygon.hpp"

namespace ravinskij
{
   using options = std::pair< double, std::size_t >;
   struct GetValue
  {
    //using SubCommand = std::function< double (options std::vector< Polygon >&) >;
    const std::vector< Polygon >& polygons;
    //std::unordered_map< std::string, SubCommand > maxSubCommands;
    //std::unordered_map< std::string, subCommand > minSubCommands;
    GetValue(const std::vector< Polygon >& vector);
   // options operator()(const std::string& subCommand);
  };

  struct AreaComparator
  {
    bool operator()(const Polygon& lhs, const Polygon& rhs);
  };

  struct VertexComparator
  {
    bool operator()(const Polygon& lhs, const Polygon& rhs);
  };

  struct GetMinMaxValue
  {
    options operator()(const std::vector< Polygon >& polygons, bool isMin, AreaComparator comp);
    options operator()(const std::vector< Polygon >& polygons, bool isMin, VertexComparator comp);
  };

  std::ostream& operator<<(std::ostream& out, const options& value);
}

#endif
