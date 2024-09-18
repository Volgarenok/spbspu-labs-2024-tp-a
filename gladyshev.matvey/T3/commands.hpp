#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include <numeric>
#include <algorithm>

#include "polygon.hpp"

namespace gladyshev
{
  void findAreas(std::istream& in, std::ostream& out, const std::vector< Polygon >& polys);
  void findMax(std::istream& in, std::ostream& out, const std::vector< Polygon >& polys);
  void findMin(std::istream& in, std::ostream& out, const std::vector< Polygon >& polys);
  void processCount(std::istream& in, std::ostream& out, const std::vector< Polygon >& polys);
  void findLessArea(std::istream& in, std::ostream& out, const std::vector< Polygon >& polys);
  void processEcho(std::istream& in, std::ostream& out, std::vector< Polygon >& polys);
}

#endif
