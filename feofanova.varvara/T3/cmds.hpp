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
  double feofanova::getArea(const std::vector< Polygon >& data) const;
  bool feofanova::isAreaLess(const std::vector< Polygon >& input, const std::vector< Polygon >& data) const;
  bool feofanova::Perms(const std::vector< Polygon >& input, const std::vector< Polygon >& data) const;
}
#endif
