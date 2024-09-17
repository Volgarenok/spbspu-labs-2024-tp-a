#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include <iosfwd>

#include "polygon.hpp"

namespace arakelyan
{
  void doArea(std::istream &in, std::ostream &out, const std::vector< Polygon > &polygons);
  void findMax(std::istream &in, std::ostream &out, const std::vector< Polygon > &polygons);
  void findMin(std::istream &in, std::ostream &out, const std::vector< Polygon > &polygons);
  void count(std::istream &in, std::ostream &out, const std::vector< Polygon > &polygons);
  void maxSeq(std::istream &in, std::ostream &out, const std::vector< Polygon > &polygons);
  void rightShapes(std::istream &, std::ostream &out, const std::vector< Polygon > &polygons);
}

#endif
