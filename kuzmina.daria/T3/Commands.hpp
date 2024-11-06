#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <vector>
#include "Shapes.hpp"

namespace kuzmina
{
  void doArea(std::istream&, std::ostream&, const std::vector< Polygon >&);
  void doMax(std::istream&, std::ostream&, const std::vector< Polygon >&);
  void doMin(std::istream&, std::ostream&, const std::vector< Polygon >&);
  void doCount(std::istream&, std::ostream&, const std::vector< Polygon >&);
  void doRightShapes(std::ostream&, const std::vector< Polygon >&);
  void doSame(std::istream&, std::ostream&, const std::vector< Polygon >&);
}

#endif
