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
   using options = std::pair< double, size_t >;
   using SubCommand = std::function< options(const std::vector< Polygon >&) >;
   using SubCommands = std::unordered_map< std::string, SubCommand >;
   class GetValue
   {
    public:
      const std::vector< Polygon >& polygons;
      GetValue(const std::vector< Polygon >& vector);
      options operator()(const std::string& command, const std::string& subCommand);

    private:
      SubCommands maxSubCommands;
      SubCommands minSubCommands;
      std::unordered_map< std::string, SubCommands > subCommands;
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
