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
  template < class F >
  struct Option
  {
    F function;
  };
  template < class F >
  std::istream& operator>>(std::istream&, Option< F >&);

  void calculateArea(const std::map< std::string, std::function< void(const std::vector< Polygon >&, std::ostream&) > >&,
                     const std::vector< Polygon >&, std::istream&, std::ostream&);
  void find(const std::map< std::string, std::function< void(const std::vector< Polygon >&, std::ostream&) > >&,
            const std::vector< Polygon >&, std::istream&, std::ostream&);
  void count(const std::map< std::string, std::function< bool(const Polygon&) > >&, const std::vector< Polygon >&, std::istream&,
             std::ostream&);
  void perms(const std::vector< Polygon >&, std::istream&, std::ostream&);
  void rightshapes(const std::vector< Polygon >&, std::ostream&);

  namespace strategies
  {
    void SumIf(const std::vector< Polygon >&, const std::function< bool(const Polygon&) >&, std::ostream&);
    void Mean(const std::vector< Polygon >&, std::ostream&);

    Polygon Max(const std::vector< Polygon >&, const std::function< bool(const Polygon&, const Polygon&) >&);
    Polygon Min(const std::vector< Polygon >&, const std::function< bool(const Polygon&, const Polygon&) >&);
    void Vertexes(const Polygon&, std::ostream&);
    void Area(const Polygon&, std::ostream&);
  }
}

#endif
