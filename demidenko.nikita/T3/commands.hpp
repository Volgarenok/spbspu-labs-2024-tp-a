#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iosfwd>
#include <vector>
#include "geometry.hpp"

namespace demidenko
{
  void doAreaCommand(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons);
  void doMaxCommand(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons);
  void doMinCommand(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons);
  void doCountCommand(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons);
  void doEchoCommand(std::istream& in, std::ostream& out, std::vector< Polygon >& polygons);
  void doRightShapesCommand(std::ostream& out, const std::vector< Polygon >& polygons);
}

#endif
