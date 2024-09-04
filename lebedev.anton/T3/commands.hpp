#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <vector>

namespace lebedev
{
  struct Polygon;

  void getAreaCmd(const std::vector< Polygon > & polygons, std::istream & input, std::ostream & output);
  void getMaxCmd(const std::vector< Polygon > & polygons, std::istream & input, std::ostream & output);
  void getMinCmd(const std::vector< Polygon > & polygons, std::istream & input, std::ostream & output);
  void getCountCmd(const std::vector< Polygon > & polygons, std::istream & input, std::ostream & output);
}

#endif
