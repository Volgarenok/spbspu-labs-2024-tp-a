#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <map>
#include <functional>
#include <algorithm>
#include <numeric>
#include <iomanip>

#include "polygon.hpp"
#include "../common/io_scope_guard.hpp"

namespace kovtun
{
  void area(const std::vector< Polygon > & polygons, std::istream & in, std::ostream & out);

  bool isEven(const Polygon & polygon);
  bool isOdd(const Polygon & polygon);
  bool notEmpty(const Polygon & polygon);
  bool equalVertex(size_t count, const Polygon & polygon);

  double getTotalArea(const Polygon & polygon, size_t count);
  double getMeanArea(const Polygon & polygon, size_t count);

}

#endif
