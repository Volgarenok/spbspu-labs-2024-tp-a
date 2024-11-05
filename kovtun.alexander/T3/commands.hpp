#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <map>
#include <functional>

#include "polygon.hpp"


namespace kovtun
{
  void area(const std::vector< kovtun::Polygon > & polygons, std::istream & in, std::ostream & out);

  bool isEven(const kovtun::Polygon & polygon);
  bool isOdd(const kovtun::Polygon & polygon);
  bool notEmpty(const kovtun::Polygon & polygon);

  double getTotalArea(size_t count, const kovtun::Polygon & polygon);
  double getMeanArea(size_t count, const kovtun::Polygon & polygon);

}

#endif
