#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iostream>
#include <vector>

#include "polygon.hpp"

namespace zagrivnyy
{
  void area(const std::vector< Polygon > &polygons, std::istream &in, std::ostream &out);
  void minMax(const std::vector< Polygon > &polygons, bool min, std::istream &in, std::ostream &out);
  void count(const std::vector< Polygon > &polygons, std::istream &in, std::ostream &out);
  void rmecho(std::vector< Polygon > &polygons, std::istream &in, std::ostream &out);
  void intersections(const std::vector< Polygon > &polygons, std::istream &in, std::ostream &out);
}
#endif
