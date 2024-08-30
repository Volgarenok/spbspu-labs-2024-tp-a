#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <functional>
#include <iostream>
#include <map>
#include <vector>
#include "polygon.hpp"

namespace allaberdiev
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
}

#endif
