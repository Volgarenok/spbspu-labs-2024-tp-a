#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <istream>
#include <vector>
#include <string>
#include "figures_struct.hpp"

namespace nikitov
{
  void area(const std::vector< Polygon >& data, std::istream& input, std::ostream& output);

  void max(const std::vector< Polygon >& data, std::istream& input, std::ostream& output);

  void min(const std::vector< Polygon >& data, std::istream& input, std::ostream& output);

  void count(const std::vector< Polygon >& data, std::istream& input, std::ostream& output);

  void same(const std::vector< Polygon >& data, std::istream& input, std::ostream& output);

  void perms(const std::vector< Polygon >& data, std::istream& input, std::ostream& output);
}
#endif