#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include "polygon.hpp"

namespace kornienko
{
  double mean(const kornienko::Polygon & polygon);
  double evenOrOdd(const kornienko::Polygon & polygon, bool isEven);
  void area(std::istream &, std::ostream & out, const std::vector< Polygon > polygons);
}

#endif
