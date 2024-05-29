#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <functional>
#include <iostream>
#include <map>
#include <vector>
#include "polygon.hpp"

namespace ibragimov
{
  using command = std::function< void(const std::vector< Polygon >&, std::ostream&) >;
  using mapOfCommands = std::map< std::string, command >;
  void getArea(const mapOfCommands&, const std::vector< Polygon >&, std::istream&, std::ostream&);
  void find(const mapOfCommands&, const std::vector< Polygon >&, std::istream&, std::ostream&);
  void count(const mapOfCommands&, const std::vector< Polygon >&, std::istream&, std::ostream&);
  void countPerms(const std::vector< Polygon >&, std::istream&, std::ostream&);
  void countRightshapes(const std::vector< Polygon >&, std::ostream&);

  using predicate = std::function< bool(const Polygon&) >;
  using comparator = std::function< bool(const Polygon&, const Polygon&) >;
  double accumArea(const std::vector< Polygon >&);
  double accumAreaIf(const std::vector< Polygon >&, const predicate&);
  double accumMeanArea(const std::vector< Polygon >&);
  Polygon findMax(const std::vector< Polygon >&, const comparator&);
  Polygon findMin(const std::vector< Polygon >&, const comparator&);
  size_t countIf(const std::vector< Polygon >&, const predicate&);

  void outputULL(std::ostream&, const size_t&);
  void outputDouble(std::ostream&, const double&);
  void outputVertexes(std::ostream&, const Polygon&);
  void outputArea(std::ostream&, const Polygon&);
}

#endif
