#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <functional>
#include <iostream>
#include <map>
#include <vector>
#include "polygon.hpp"

namespace ibragimov
{
  // void calculateArea(const std::vector< Polygon >&, std::istream&, std::ostream&);
  template < class S >
  void find(const std::map< std::string, std::function< bool(Polygon, Polygon) > >&, const std::vector< Polygon >&, std::istream&,
            std::ostream&);
  void count(const std::map< std::string, std::function< bool(Polygon) > >&, const std::vector< Polygon >&, std::istream&, std::ostream&);

  namespace strategies
  {
    struct Max
    {
      static void compare(const std::vector< Polygon >&, const std::function< bool(Polygon, Polygon) >&, std::ostream&);
    };
    struct Min
    {
      static void compare(const std::vector< Polygon >&, const std::function< bool(Polygon, Polygon) >&, std::ostream&);
    };
  }

  template < class S >
  void find(const std::map< std::string, std::function< bool(Polygon, Polygon) > >& options, const std::vector< Polygon >& polygons,
            std::istream& in, std::ostream& out)
  {
    std::function< bool(Polygon, Polygon) > comparator;

    std::string input = "";
    in >> input;

    try
    {
      comparator = options.at(input);
    }
    catch (...)
    {
      throw;
    }

    S::compare(polygons, comparator, out);
  }
}

#endif
