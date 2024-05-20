#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include "polygon.hpp"

namespace kornienko
{
  void area(std::istream &, std::ostream & out, const std::vector< Polygon > polygons);
  void minOrMax(std::istream &, std::ostream & out, const std::vector< Polygon > polygons, bool isMax);
}

#endif
