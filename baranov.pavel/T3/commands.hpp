#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <vector>
#include <functional>
#include "polygon.hpp"

namespace baranov
{
  void area(std::vector< Polygon > & shapes, std::istream & in, std::ostream & out);
  void max(std::vector< Polygon > & shapes, std::istream & in, std::ostream & out);
  void min(std::vector< Polygon > & shapes, std::istream & in, std::ostream & out);
  void count(std::vector< Polygon > & shapes, std::istream & in, std::ostream & out);
  void rect(std::vector< Polygon > & shapes, std::istream &, std::ostream & out);
  void inFrame(std::vector< Polygon > & shapes, std::istream & in, std::ostream & out);
  void lessArea(std::vector< Polygon > & shapes, std::istream & in, std::ostream & out);
}

#endif

