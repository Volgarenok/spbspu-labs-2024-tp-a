#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include <iosfwd>
#include "polygon.hpp"

namespace erohin
{
  void isInFrame(const std::vector< Polygon > & context, std::istream & input, std::ostream & output);
  void countRightShapes(const std::vector< Polygon > & context, std::istream & input, std::ostream & output);
  namespace detail
  {
    bool isInFrameImpl(const std::vector< Polygon > & context, Polygon & argument);
    size_t countRightShapesImpl(const std::vector< Polygon > & context);
  }
}

#endif
