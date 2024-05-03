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
  void calculateArea(const std::map< std::string, std::function< bool(Polygon) > >&,
                     const std::map< std::string, std::function< double(std::vector< Polygon >) > >&, const std::vector< Polygon >&,
                     std::istream&, std::ostream&);
  template < class S >
  void find(const std::map< std::string, std::function< bool(Polygon, Polygon) > >&,
            const std::map< std::string, std::function< void(Polygon, std::ostream&) > >&, const std::vector< Polygon >&, std::istream&,
            std::ostream&);
  void count(const std::map< std::string, std::function< bool(Polygon) > >&, const std::vector< Polygon >&, std::istream&, std::ostream&);

  namespace strategies
  {
    double Sum(const std::vector< Polygon >&);
    double Mean(const std::vector< Polygon >&);
    void Size(const Polygon&, std::ostream&);
    void Area(const Polygon&, std::ostream&);

    struct Max
    {
      static Polygon find(const std::vector< Polygon >&, const std::function< bool(Polygon, Polygon) >&);
    };
    struct Min
    {
      static Polygon find(const std::vector< Polygon >&, const std::function< bool(Polygon, Polygon) >&);
    };
  }

  template < class S >
  void find(const std::map< std::string, std::function< bool(Polygon, Polygon) > >& options,
            const std::map< std::string, std::function< void(Polygon, std::ostream&) > >& strategies,
            const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    std::function< bool(Polygon, Polygon) > comparator;
    std::function< void(Polygon, std::ostream&) > strategy;

    std::string input = "";
    in >> input;

    try
    {
      comparator = options.at(input);
      strategy = strategies.at(input);
    }
    catch (...)
    {
      throw;
    }

    strategy(S::find(polygons, comparator), out);
  }
}

#endif
