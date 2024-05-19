#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include "polygon.hpp"

namespace kornienko
{
  double evenOrOdd(const kornienko::Polygon & polygon, bool isEven);
  double mean(const kornienko::Polygon & polygon);
  double numOfVertexes(const kornienko::Polygon & polygon, int num);
  void area(std::istream &, std::ostream & out, const std::vector< Polygon > polygons);
}

#endif
