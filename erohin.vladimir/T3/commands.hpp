#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include <iosfwd>
#include "polygon.hpp"

namespace erohin
{
  void doAreaCommand(const std::vector< Polygon > & context, std::istream & input, std::ostream & output);
  double evaluateAreaNum(const std::vector< Polygon > & context, size_t number);
  double evaluateAreaEven(const std::vector< Polygon > & context);
  double evaluateAreaOdd(const std::vector< Polygon > & context);
  double evaluateAreaMean(const std::vector< Polygon > & context);
  void doMaxCommand(const std::vector< Polygon > & context, std::istream & input, std::ostream & output);
  void findMaxAreaPolygon(const std::vector< Polygon > & context, std::ostream & output);
  void findMaxVertexesPolygon(const std::vector< Polygon > & context, std::ostream & output);
  void doMinCommand(const std::vector< Polygon > & context, std::istream & input, std::ostream & output);
  void findMinAreaPolygon(const std::vector< Polygon > & context, std::ostream & output);
  void findMinVertexesPolygon(const std::vector< Polygon > & context, std::ostream & output);
  void doCountCommand(const std::vector< Polygon > & context, std::istream & input, std::ostream & output);
  void doInFrameCommand(const std::vector< Polygon > & context, std::istream & input, std::ostream & output);
  void doRightShapesCommand(const std::vector< Polygon > & context, std::istream & input, std::ostream & output);
}

#endif
