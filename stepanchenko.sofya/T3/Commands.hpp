#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "Polygon.hpp"
#include "Commands.hpp"

namespace stepanchenko
{
  void areaCmd(const std::vector< Polygon > & polygons, std::istream& in, std::ostream& out);
  void maxCmd(std::vector< Polygon > polygons, std::istream& in, std::ostream& out);
  void minCmd(std::vector< Polygon > polygons, std::istream& in, std::ostream& out);
  void countCmd(std::vector< Polygon > polygons, std::istream& in, std::ostream& out);

  void maxSeqCmd(std::vector< Polygon > polygons, std::istream& in, std::ostream& out);
  void rmechoCmd(std::vector< Polygon > polygons, std::istream& in, std::ostream& out);
  void inframeCmd(std::vector< Polygon > polygons, std::istream& in, std::ostream& out);
}

#endif
