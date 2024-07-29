#ifndef CMDS_HPP
#define CMDS_HPP

#include "geometryFunc.hpp"

namespace skuratov
{
  void area(std::istream& in, std::ostream& out, const std::vector< Polygon >& poly);
  void max(std::istream& in, std::ostream& out, const std::vector< Polygon >& poly);
  void min(std::istream& in, std::ostream& out, const std::vector< Polygon >& poly);
  void count(std::istream& in, std::ostream& out, const std::vector< Polygon >& poly);

  void lessArea(std::istream& in, std::ostream& out, const std::vector< Polygon >& poly);
  void inFrame(std::istream& in, std::ostream& out, const std::vector< Polygon >& poly);
  void rightShapes(std::ostream& out, const std::vector< Polygon >& poly);
}

#endif
