#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "polygon.hpp"
#include <vector>

namespace piyavkin
{
  void getArea(std::istream& in, std::ostream& out, const std::vector< Polygon >& pol);
  void getMinMax(std::istream& in, std::ostream& out, const std::vector< Polygon >& pol, bool min);
  void count(std::istream& in, std::ostream& out, const std::vector< Polygon >& pol);
  void lessArea(std::istream& in, std::ostream& out, const std::vector< Polygon >& pol);
}
#endif