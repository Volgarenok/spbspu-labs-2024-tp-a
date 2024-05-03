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
  void findMax(const std::map< std::string, std::function< bool(Polygon, Polygon) > >&,
            const std::map< std::string, std::function< void(Polygon, std::ostream&) > >&, const std::vector< Polygon >&, std::istream&,
            std::ostream&);
  void findMin(const std::map< std::string, std::function< bool(Polygon, Polygon) > >&,
            const std::map< std::string, std::function< void(Polygon, std::ostream&) > >&, const std::vector< Polygon >&, std::istream&,
            std::ostream&);
  void count(const std::map< std::string, std::function< bool(Polygon) > >&, const std::vector< Polygon >&, std::istream&, std::ostream&);

  namespace strategies
  {
    double Sum(const std::vector< Polygon >&);
    double Mean(const std::vector< Polygon >&);
    void Size(const Polygon&, std::ostream&);
    void Area(const Polygon&, std::ostream&);
  }

}

#endif
