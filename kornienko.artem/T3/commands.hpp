#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include "polygon.hpp"

namespace kornienko
{
  void getArea(std::istream &, std::ostream & out, std::vector< Polygon > polygons);
}

#endif
