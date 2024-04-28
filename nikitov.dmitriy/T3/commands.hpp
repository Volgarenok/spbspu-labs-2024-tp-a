#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <istream>
#include <vector>
#include <string>
#include <figures_struct.hpp>

namespace nikitov
{
  void area(std::vector< Polygon >& data, std::istream& input, std::ostream& output);

  void max(std::vector< Polygon >& data, std::istream& input, std::ostream& output);

  void min(std::vector< Polygon >& data, std::istream& input, std::ostream& output);

  void count(std::vector< Polygon >& data, std::istream& input, std::ostream& output);

  void same(std::vector< Polygon >& data, std::istream& input, std::ostream& output);

  void perms(std::vector< Polygon >& data, std::istream& input, std::ostream& output);
}
#endif