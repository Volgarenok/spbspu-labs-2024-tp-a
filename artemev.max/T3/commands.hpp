#ifndef COMMANDS_HPP
#define COMMANDS

#include <istream>
#include <vector>
#include "shapes.hpp"

namespace artemev
{
  void area(const std::vector< Polygon >& data, std::istream& input, std::ostream& output);
  void max(const std::vector< Polygon >& data, std::istream& input, std::ostream& output);
  void min(const std::vector< Polygon >& data, std::istream& input, std::ostream& output);
  void count(const std::vector< Polygon >& data, std::istream& input, std::ostream& output);
  void perms(const std::vector< Polygon >& data, std::istream& input, std::ostream& output);
  void rightshapes(const std::vector< Polygon >& data, std::istream& input, std::ostream& output);
}

#endif
