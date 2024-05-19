#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include "polygon.hpp"

namespace kornienko
{
  double evenOrOddArea(const kornienko::Polygon & polygon, bool isEven);
  double meanArea(const kornienko::Polygon & polygon);
  double numOfVertexesArea(const kornienko::Polygon & polygon, size_t num);
  void area(std::istream &, std::ostream & out, const std::vector< Polygon > polygons);
  void minOrMax(std::istream &, std::ostream & out, const std::vector< Polygon > polygons, bool isMax);
}

#endif
