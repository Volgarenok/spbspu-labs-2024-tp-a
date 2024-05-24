#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iosfwd>
#include <vector>
#include <map>
#include <functional>
#include "polygon.hpp"

namespace strelyaev
{
  void count_cmd(std::ostream&,
      std::istream&,
      const std::vector< Polygon >&,
      const std::map< std::string, std::function< bool(const Polygon&) > >&);

  void area_cmd(std::ostream&,
      std::istream&,
      const std::vector< Polygon >&,
      const std::map< std::string, std::function< bool(const Polygon&) > >&);

  void max_cmd(std::ostream& out, std::istream& in,
      const std::vector< Polygon >& polygons_vector);

  void min_cmd(std::ostream& out, std::istream& in,
      const std::vector< Polygon >& polygons_vector);

  void perms_cmd(std::ostream& out, std::istream& in,
      const std::vector< Polygon >& polygons_vector);

  void maxseq_cmd(std::ostream& out, std::istream& in,
      const std::vector< Polygon >& polygons_vector);

  bool permutation_polygons(const Polygon& lhs, const Polygon& rhs);
  size_t isEqualCounter(const Polygon& plg, const std::vector< Point >& src, size_t& counter);
}

#endif

