#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>

#include "polygon.hpp"

namespace gladyshev
{
  findAreas(std::istream& in, const std::vector< Polygon > polys);
  findMax(std::istream& in, const std::vector< Polygon > polys);
  findMin(std::istream& in, const std::vector< Polygon > polys);
  processCount(std::istream& in, const std::vector< Polygon > polys);
  findLessArea(std::istream& in, const std::vector< Polygon > polys);
  processEcho(std::istream& in, const std::vector< Polygon > polys);
}

#endif
