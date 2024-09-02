#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iosfwd>
#include <vector>
#include <map>
#include <functional>
#include "polygon.hpp"

namespace strelyaev
{
  void count(std::ostream&,
      std::istream&,
      const std::vector< Polygon >&,
      const std::map< std::string, std::function< bool(const Polygon&) > >&);

  void getArea(std::ostream&,
      std::istream&,
      const std::vector< Polygon >&,
      const std::map< std::string, std::function< bool(const Polygon&) > >&);

  void findMax(std::ostream& out, std::istream& in,
      const std::vector< Polygon >& polygons_vector);

  void findMin(std::ostream& out, std::istream& in,
      const std::vector< Polygon >& polygons_vector);

  void getPerms(std::ostream& out, std::istream& in,
      const std::vector< Polygon >& polygons_vector);

  void getMaxSeq(std::ostream& out, std::istream& in,
      const std::vector< Polygon >& polygons_vector);

  bool isPermutationPolygons(const Polygon& lhs, const Polygon& rhs);
  size_t getEqualCounter(const Polygon& plg, const std::vector< Point >& src, size_t& counter);
}

#endif

