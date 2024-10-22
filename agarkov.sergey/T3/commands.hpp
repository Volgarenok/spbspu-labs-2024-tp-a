#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <vector>
#include <ostream>
#include "polygon.hpp"

namespace agarkov
{
  void getAreaEven(const std::vector< Polygon >& polygons, std::ostream& out);
  void getAreaOdd(const std::vector< Polygon >& polygons, std::ostream& out);
}

#endif
