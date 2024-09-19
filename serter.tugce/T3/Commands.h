#ifndef COMMANDS_H
#define COMMANDS_H

#include <vector>
#include "Geometry.h"

namespace serter
{
  void echo(std::vector< Polygon >& polygons, std::istream& input, std::ostream& output);
  void rmEcho(std::vector< Polygon >& polygons, std::istream& input, std::ostream& output);
  void lessArea(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& output);
}

#endif

