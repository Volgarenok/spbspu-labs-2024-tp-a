#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "polygon.hpp"

namespace zakozhurnikova
{
  void doAreaCommand(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void doMaxCommand(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void doMinCommand(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void doCountCommand(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void doIntersectionsCommand(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void doRmechoCommand(std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
}
#endif
