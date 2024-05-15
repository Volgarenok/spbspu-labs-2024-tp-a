#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include <iosfwd>
#include "polygon.hpp"

namespace erohin
{
  void doAreaCommand(const std::vector< Polygon > & context, std::istream & input, std::ostream & output);
  double countAreaNum(const std::vector< Polygon > & context, size_t number);
  double countAreaEven(const std::vector< Polygon > & context);
  double countAreaOdd(const std::vector< Polygon > & context);
  double countAreaMean(const std::vector< Polygon > & context);
  void doInFrameCommand(const std::vector< Polygon > & context, std::istream & input, std::ostream & output);
  void doRightShapesCommand(const std::vector< Polygon > & context, std::istream & input, std::ostream & output);
}

#endif
