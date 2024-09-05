#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iostream>
#include <vector>
#include "polygon.hpp"

namespace feofanova
{
  double getArea(const Polygon& polygon);
  bool isAreaLess(const Polygon& p1, const Polygon& p2);
  bool countPerms(const Polygon& p1, const Polygon& p2);
  void Count(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void Perms(const std::vector< Polygon >& data, std::istream& in, std::ostream& out);
  void Lessarea(const std::vector< Polygon >& data, std::istream& in, std::ostream& out)
}
#endif
