#include "commands.hpp"
#include "area.hpp"
#include "geometry.hpp"

void demidenko::area(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons);
void demidenko::max(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons);
void demidenko::min(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons);
void demidenko::count(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons);
void demidenko::echo(std::istream& in, std::ostream& out, std::vector< Polygon >& polygons);
void demidenko::rightShapes(
  std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons
);
