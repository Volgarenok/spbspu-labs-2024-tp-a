#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iostream>
#include <vector>

#include "polygon.hpp"

namespace zagrivnyy
{
  void area(const std::vector< Polygon > &polygons, std::istream &in, std::ostream &out);
}
#endif
