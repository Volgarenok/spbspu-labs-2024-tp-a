#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iosfwd>
#include <vector>
#include "polygon.hpp"

namespace vyzhanov
{
  void area(const std::vector< Polygon >&, std::istream&, std::ostream&);
  void max(const std::vector< Polygon >&, std::istream&, std::ostream&);
  void min(const std::vector< Polygon >&, std::istream&, std::ostream&);
  void count(const std::vector< Polygon >&, std::istream&, std::ostream&);
  void lessarea(const std::vector< Polygon >&, std::istream&, std::ostream&);
  void reacts(const std::vector< Polygon >&, std::istream&, std::ostream&);
  void rmecho(const std::vector< Polygon >&, std::istream&, std::ostream&);
}

#endif
