#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <map>
#include <functional>

#include "polygon.hpp"


namespace kovtun
{
  void area(const std::vector< Polygon > & polygons, std::istream & in, std::ostream & out);

  bool isEven(const Polygon & polygon);
  bool isOdd(const Polygon & polygon);
  bool notEmpty(const Polygon & polygon);
  bool equalVertex(size_t count, const Polygon & polygon);

  double getTotalArea(size_t count, const Polygon & polygon);
  double getMeanArea(size_t count, const Polygon & polygon);

}

#endif
