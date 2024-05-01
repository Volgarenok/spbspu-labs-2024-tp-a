#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <vector>
#include "polygon.hpp"

namespace ibragimov
{
  // void calculateArea(const std::vector< Polygon >&, std::istream&, std::ostream&);
  void findMax(const std::vector< Polygon >&, std::istream&, std::ostream&);
  void findMin(const std::vector< Polygon >&, std::istream&, std::ostream&);
  void count(const std::vector< Polygon >&, std::istream&, std::ostream&);
}

#endif
