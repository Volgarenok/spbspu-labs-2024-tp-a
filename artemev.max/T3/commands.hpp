#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <istream>
#include <vector>
#include "shapes.hpp"

namespace artemev
{
  void getAreaCmd(const std::vector< Polygon >& figure, std::istream& input, std::ostream& output);
  void getMaxCmd(const std::vector< Polygon >& figure, std::istream& input, std::ostream& output);
  void getMinCmd(const std::vector< Polygon >& figure, std::istream& input, std::ostream& output);
  void getCountCmd(const std::vector< Polygon >& figure, std::istream& input, std::ostream& output);
  void getPermsCmd(const std::vector< Polygon >& figure, std::istream& input, std::ostream& output);
  void getRightShapesCmd(const std::vector< Polygon >& figure, std::ostream& output);
}

#endif
