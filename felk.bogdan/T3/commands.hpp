#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include "polygon.hpp"

namespace felk
{
  void area(std::istream&, std::ostream&, const std::vector< Polygon >&);
  void max(std::istream&, std::ostream&, const std::vector< Polygon >&);
  void min(std::istream&, std::ostream&, const std::vector< Polygon >&);
  void count(std::istream&, std::ostream&, const std::vector< Polygon >&);
  void inFrame(std::istream&, std::ostream&, const std::vector< Polygon >&);
  void echo(std::istream&, std::ostream&, std::vector< Polygon >&);
  void maxSeq(std::istream&, std::ostream&, const std::vector< Polygon >&);
}

#endif
