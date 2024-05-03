#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include <iosfwd>
#include "polygon.hpp"

namespace erohin
{
  void doInFrame(const std::vector< Polygon > & context, std::istream & input, std::ostream & output);
  void doRightShapes(const std::vector< Polygon > & context, std::istream & input, std::ostream & output);
  bool isInFrame(const std::vector< Polygon > & context, const Polygon & argument);
  size_t countRightShapes(const std::vector< Polygon > & context);
}

#endif
