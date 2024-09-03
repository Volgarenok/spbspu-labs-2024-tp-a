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
      options operator()(const std::string& command);

    private:
      SubCommands maxSubCommands;
      SubCommands minSubCommands;
   };

  struct AreaComparator
  {
    bool operator()(const Polygon& lhs, const Polygon& rhs);
  };

  struct VertexComparator
  {
    bool operator()(const Polygon& lhs, const Polygon& rhs);
  };

  struct GetMinValue
  {
    options operator()(const std::vector< Polygon >& polygons, AreaComparator comp);
    options operator()(const std::vector< Polygon >& polygons, VertexComparator comp);
  };

  struct GetMaxValue
  {
    options operator()(const std::vector< Polygon >& polygons, AreaComparator comp);
    options operator()(const std::vector< Polygon >& polygons, VertexComparator comp);
  };


  std::ostream& operator<<(std::ostream& out, const options& value);
}

#endif
