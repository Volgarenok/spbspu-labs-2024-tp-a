#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <vector>
#include "polygon.hpp"

namespace basko
{
  void area(const std::vector< Polygon >& value, std::istream& in, std::ostream& out);
  void max(const std::vector< Polygon >& value, std::istream& in, std::ostream& out);
  void min(const std::vector< Polygon >& value, std::istream& in, std::ostream& out);
  void count(const std::vector< Polygon >& value, std::istream& in, std::ostream& out);
  void rightshapes(const std::vector< Polygon >& value, std::ostream& out);
  void echo(std::vector< Polygon >& value, std::istream& in, std::ostream& out);
  void inframe(const std::vector< Polygon >& value, std::istream& in, std::ostream& out);
}

#endif
