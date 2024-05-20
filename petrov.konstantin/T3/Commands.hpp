#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include <iostream>
#include "Geometry.hpp"
#include "Utils.hpp"

namespace petrov
{
  void cmdArea(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void cmdExtremum(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out, bool forMax);
  void cmdCount(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void cmdRmEcho(std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void cmdSame(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
}

#endif
