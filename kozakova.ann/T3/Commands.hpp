#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include "Polygon.hpp"

namespace kozakova
{
  void doAreaCommand(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void doMaxCommand(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void doMinCommand(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void doCountCommand(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void doRectsCommand(const std::vector< Polygon >& polygons, std::ostream& out);
  void doMaxseqCommand(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
}

#endif
