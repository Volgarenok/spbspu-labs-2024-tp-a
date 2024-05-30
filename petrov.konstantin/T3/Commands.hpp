#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include <iostream>
#include "Geometry.hpp"

namespace petrov
{
  void cmdArea(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void cmdMax(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void cmdMin(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void cmdCount(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void cmdRmEcho(std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void cmdSame(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
}

#endif
