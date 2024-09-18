#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iosfwd>
#include <vector>
#include <map>
#include <functional>
#include "polygon.hpp"

namespace altun
{
  void count(std::istream&, std::ostream&,
      const std::vector< Polygon >&,
      const std::map< std::string, std::function< bool(const Polygon&) > >&);

  void getArea(std::istream&, std::ostream&,
      const std::vector< Polygon >&,
      const std::map< std::string, std::function< bool(const Polygon&) > >&);

  void findMax(std::istream&, std::ostream&,
      const std::vector< Polygon >&);

  void findMin(std::istream&, std::ostream&,
      const std::vector< Polygon >&);

  void maxSeq(std::istream&, std::ostream&,
      const std::vector< Polygon >&);

  void echo(std::istream&, std::ostream&,
      std::vector< Polygon >&);

  void same(std::istream&, std::ostream&,
      const std::vector< Polygon >);
}

#endif
