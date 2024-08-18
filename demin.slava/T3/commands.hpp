#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iostream>
#include <vector>

#include "figures.hpp"

namespace demin
{
  void doarea(const std::vector< Polygon > &polygons, std::istream &in, std::ostream &out);
  void domin(const std::vector< Polygon > &polygons, std::istream &in, std::ostream &out);
  void domax(const std::vector< Polygon > &polygons, std::istream &in, std::ostream &out);
  void count(const std::vector< Polygon > &polygons, std::istream &in, std::ostream &out);
}
#endif
