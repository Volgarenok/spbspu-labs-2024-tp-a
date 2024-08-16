#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <vector>
#include "polygon.hpp"

namespace ayupov
{
  void area(const std::vector< Polygon >&, std::istream&, std::ostream&);
  void max(const std::vector< Polygon >&, std::istream&, std::ostream&);
  void min(const std::vector< Polygon >&, std::istream&, std::ostream&);
  void count(const std::vector< Polygon >&, std::istream&, std::ostream&);
  void echo(std::vector< Polygon >&, std::istream&, std::ostream&);
  void inFrame(const std::vector< Polygon >&, std::istream&, std::ostream&);
  void maxSeq(const std::vector< Polygon >&, std::istream&, std::ostream&);
  void lessArea(const std::vector< Polygon >&, std::istream&, std::ostream&);
}

#endif
