#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <vector>
#include "polygon.h"

namespace basko
{
  void area(const std::vector< Polygon >& value, std::istream& in, std::ostream& out);
}
