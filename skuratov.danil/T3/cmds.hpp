#ifndef CMDS_HPP
#define CMDS_HPP

#include "polygon.hpp"

namespace skuratov
{
  void area(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygon);
  void max(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygon);
  void min(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygon);
  void count(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygon);

  void lessArea(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygon);
  void inFrame(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygon);
  void rightShapes(std::ostream& out, const std::vector< Polygon >& polygon);
}

#endif
