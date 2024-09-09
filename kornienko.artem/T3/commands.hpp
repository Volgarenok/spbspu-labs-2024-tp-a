#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include "polygon.hpp"

namespace kornienko
{
  void area(std::istream &, std::ostream & out, const std::vector< Polygon > polygons);
  void minVertexOrArea(std::istream & in, std::ostream & out, const std::vector< Polygon > polygons);
  void maxVertexOrArea(std::istream & in, std::ostream & out, const std::vector< Polygon > polygons);
  void count(std::istream & in, std::ostream & out, const std::vector< Polygon > polygons);
  void lessArea(std::istream &, std::ostream & out, const std::vector< Polygon > polygons);
  void same(std::istream &, std::ostream & out, const std::vector< Polygon > polygons);
}

#endif
