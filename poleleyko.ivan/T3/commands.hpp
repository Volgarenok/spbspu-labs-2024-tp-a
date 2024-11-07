#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <vector>
#include <functional>
#include "polygon.hpp"

namespace poleleyko
{
  void area(const std::vector< Polygon > & shapes, std::istream & in, std::ostream & out);
  void max(const std::vector< Polygon > & shapes, std::istream & in, std::ostream & out);
  void min(const std::vector< Polygon > & shapes, std::istream & in, std::ostream & out);
  void count(const std::vector< Polygon > & shapes, std::istream & in, std::ostream & out);
  void rect(const std::vector< Polygon > & shapes, std::istream &, std::ostream & out);
  void inFrame(const std::vector< Polygon > & shapes, std::istream & in, std::ostream & out);
  void lessArea(const std::vector< Polygon > & shapes, std::istream & in, std::ostream & out);
}

#endif