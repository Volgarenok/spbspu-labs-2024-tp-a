#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <istream>
#include <vector>
#include "figures_struct.hpp"

namespace nikitov
{
  void areaCmd(const std::vector< Polygon >& data, std::istream& input, std::ostream& output);
  void maxCmd(const std::vector< Polygon >& data, std::istream& input, std::ostream& output);
  void minCmd(const std::vector< Polygon >& data, std::istream& input, std::ostream& output);
  void countCmd(const std::vector< Polygon >& data, std::istream& input, std::ostream& output);
  void sameCmd(const std::vector< Polygon >& data, std::istream& input, std::ostream& output);
  void permsCmd(const std::vector< Polygon >& data, std::istream& input, std::ostream& output);
}
#endif
