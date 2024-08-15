#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <vector>
#include "Polygon.hpp"

namespace yakshieva
{
  void doAreaCommand(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void doMaxCommand(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void doMinCommand(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void doCountCommand(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void doLessAreaCommand(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void doRmechoCommand(std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void duplicateEntries(std::vector<Polygon>& p, const Polygon& targetP);
  void doEchoCommand(std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
}

#endif
