#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <istream>
#include <iomanip>
#include <functional>
#include <algorithm>
#include <numeric>
#include <vector>
#include "StreamGuard.hpp"
#include "polygon.hpp"

namespace feofanova
{
  double getArea(const std::vector< Polygon >& data) const;
  bool isAreaLess(const std::vector< Polygon >& input, const std::vector< Polygon >& data) const;
  bool Perms(const std::vector< Polygon >& input, const std::vector< Polygon >& data) const;
}
#endif
