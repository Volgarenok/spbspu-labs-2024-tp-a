#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <functional>
#include <iostream>
#include <map>
#include <vector>
#include "polygon.hpp"

namespace ibragimov
{
  // void calculateArea(const std::vector< Polygon >&, std::istream&, std::ostream&);
  void findMax(const std::map< std::string, std::function< bool(Polygon, Polygon) > >&, const std::vector< Polygon >&, std::istream&,
               std::ostream&);
  void findMin(const std::map< std::string, std::function< bool(Polygon, Polygon) > >&, const std::vector< Polygon >&, std::istream&,
               std::ostream&);
  void count(const std::map< std::string, std::function< bool(Polygon) > >&, const std::vector< Polygon >&, std::istream&,
               std::ostream&);
}

#endif
