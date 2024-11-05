#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <vector>
#include "polygon.hpp"

namespace skopchenko
{
  void getMax(const std::vector< Polygon >& data, std::istream& in, std::ostream& out);
  void getMin(const std::vector< Polygon >& data, std::istream& in, std::ostream& out);
}

#endif
