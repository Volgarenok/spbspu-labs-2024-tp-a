#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iostream>
#include <vector>
#include "polygon.hpp"

namespace grechishnikov
{
  void area(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void max(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void min(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void count(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void perms(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void maxseq(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
}

#endif
