#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <vector>
#include "polygon.hpp"

namespace ibragimov
{
  void getArea(const std::map< std::string, std::function< void(const std::vector< Polygon >&, std::ostream&) > >&,
                     const std::vector< Polygon >&, std::istream&, std::ostream&);
  void find(const std::map< std::string, std::function< void(const std::vector< Polygon >&, std::ostream&) > >&,
            const std::vector< Polygon >&, std::istream&, std::ostream&);
  void count(const std::map< std::string, std::function< void(const std::vector< Polygon >&, std::ostream&) > >&,
             const std::vector< Polygon >&, std::istream&, std::ostream&);
  void countPerms(const std::vector< Polygon >&, std::istream&, std::ostream&);
  void countRightshapes(const std::vector< Polygon >&, std::ostream&);

  bool isCorrectNumber(const std::string&);
  std::function< void(const std::vector< Polygon >&, std::ostream&) >
  getCommand(const std::string&, const std::map< std::string, std::function< void(const std::vector< Polygon >&, std::ostream&) > >&);

  double sumArea(const std::vector< Polygon >& values);
  double sumAreaIf(const std::vector< Polygon >&, const std::function< bool(const Polygon&) >&);
  double sumAreaMean(const std::vector< Polygon >&);
  ibragimov::Polygon findMax(const std::vector< Polygon >&, const std::function< bool(const Polygon&, const Polygon&) >&);
  ibragimov::Polygon findMin(const std::vector< Polygon >&, const std::function< bool(const Polygon&, const Polygon&) >&);
  size_t countIf(const std::vector< Polygon >&, const std::function< bool(const Polygon&) >&);
  bool isPermutation(const Polygon&, const Polygon&);
  bool isContainingRightAngles(const Polygon& rhs);

  void outputULL(std::ostream&, const size_t&);
  void outputDouble(std::ostream&, const double&);
  void outputVertexes(std::ostream&, const Polygon&);
  void outputArea(std::ostream&, const Polygon&);
}

#endif
