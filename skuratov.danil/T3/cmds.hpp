#ifndef CMDS_HPP
#define CMDS_HPP

#include "polygon.hpp"

namespace skuratov
{
  void area(std::istream&, std::ostream&, const std::vector< Polygon >& polygon);
  void max(std::istream&, std::ostream&, const std::vector< Polygon >& polygon);
  void min(std::istream&, std::ostream&, const std::vector< Polygon >& polygon);
  void count(std::istream&, std::ostream&, const std::vector< Polygon >& polygon);

  void lessArea(std::istream&, std::ostream&, const std::vector< Polygon >& polygon);
  void inFrame(std::istream&, std::ostream&, const std::vector< Polygon >& polygon);
  void rightShapes(std::ostream&, const std::vector< Polygon >& polygon);
}

#endif
