#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <vector>
#include "polygon.hpp"

namespace ibragimov
{
  // double calculateArea(const std::vector< Polygon >&, std::istream&, std::ostream&);
  // double findMax(const std::vector< Polygon >&);
  // double findMin(const std::vector< Polygon >&);
  void count(const std::vector< Polygon >&, std::istream&, std::ostream&);
}

#endif
