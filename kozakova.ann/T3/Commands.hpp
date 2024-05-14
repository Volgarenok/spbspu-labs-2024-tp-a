#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include "Polygon.hpp"

namespace kozakova
{
  void areaCmd(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void maxCmd(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void minCmd(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void countCmd(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void rectsCmd(const std::vector< Polygon >& polygons, std::ostream& out);
  void maxseqCmd(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
}

#endif
