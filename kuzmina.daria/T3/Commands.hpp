#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <vector>
#include "Shapes.hpp"

namespace kuzmina
{
  void area(std::istream&, std::ostream&, const std::vector< Polygon >&);
  void max(std::istream&, std::ostream&, const std::vector< Polygon >&);
  void min(std::istream&, std::ostream&, const std::vector< Polygon >&);
  void count(std::istream&, std::ostream&, const std::vector< Polygon >&);

  void same(std::istream&, std::ostream&, const std::vector< Polygon >&);
  void rightshapes(std::istream&, std::ostream&, const std::vector< Polygon >&);
}


#endif
