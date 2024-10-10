#ifndef COMMANDS_H
#define COMMANDS_H

#include <vector>
#include "Geometry.h"

namespace serter
{
  void area(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& output);
  void min(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& output);
  void max(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& output);
  void count(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& output);
  void echo(std::vector< Polygon >& polygons, std::istream& input, std::ostream& output);
  void rmEcho(std::vector< Polygon >& polygons, std::istream& input, std::ostream& output);
  void lessArea(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& output);
}

#endif
