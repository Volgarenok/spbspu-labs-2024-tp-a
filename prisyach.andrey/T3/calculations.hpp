#ifndef CALCULATIONS_HPP
#define CALCULATIONS_HPP

#include <vector>
#include <iostream>
#include "geometric.hpp"

namespace prisyach
{
  void doArea(const std::vector< Polygon > & polygons, std::istream & in, std::ostream & out);
  void doMax(const std::vector< Polygon > & polygons, std::istream & in, std::ostream & out);
  void doMin(const std::vector< Polygon > & polygons, std::istream & in, std::ostream & out);
  void doCount(const std::vector< Polygon > & polygons, std::istream & in, std::ostream & out);
  void doPerms(const std::vector< Polygon > & polygons, std::istream & in, std::ostream & out);
  void doMaxSeq(const std::vector< Polygon > & polygons, std::istream & in, std::ostream & out);
  void doRmEcho(std::vector< Polygon > & polygons, std::istream & in, std::ostream & out);
}

#endif
