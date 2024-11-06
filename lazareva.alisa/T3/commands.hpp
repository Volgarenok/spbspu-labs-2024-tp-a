#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iostream>
#include <vector>
#include "figures.hpp"

namespace lazareva
{
  double getArea(const Polygon& polygon);
  void Count(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void countArea(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void countMin(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void countMax(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void rectsCommand(std::ostream& out, const std::vector< Polygon >& polygons);
  bool isRectangle(const Polygon& polygon);
  void inframe(const std::vector< Polygon >& value, std::istream& in, std::ostream& out);
  bool countPerms(const Polygon& p1, const Polygon& p2)
  void Perms(const std::vector< Polygon >& data, std::istream& in, std::ostream& out);
}
#endif
