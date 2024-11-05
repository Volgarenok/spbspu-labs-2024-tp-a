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
  void area(const std::vector< Polygon > &, std::istream &, std::ostream &);
  void max(const std::vector< Polygon > &, std::istream &, std::ostream &);
  void min(const std::vector< Polygon > &, std::istream &, std::ostream &);
  void count(const std::vector< Polygon > &, std::istream &, std::ostream &);
  void lessArea(const std::vector< Polygon > &, std::istream &, std::ostream &);

  bool isEven(const Polygon &);
  bool isOdd(const Polygon &);
  bool notEmpty(const Polygon &);
  bool equalVertex(size_t, const Polygon &);

  double getTotalArea(const Polygon &, size_t);
  double getMeanArea(const Polygon &, size_t);

  bool area_comparator(const Polygon &, const Polygon &);
  bool vertex_comparator(const Polygon &, const Polygon &);
}

#endif
