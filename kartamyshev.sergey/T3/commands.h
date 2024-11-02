#ifndef COMMANDS_H
#define COMMANDS_H

#include <iostream>
#include <vector>
#include "Polygon.h"

namespace kartamyshev
{
  void area(const std::vector< Polygon >& data, std::istream& input, std::ostream& output);
  void max(const std::vector< Polygon >& data, std::istream& input, std::ostream& output);
  void min(const std::vector< Polygon >& data, std::istream& input, std::ostream& output);
  void count(const std::vector< Polygon >& data, std::istream& input, std::ostream& output);
  void same(const std::vector< Polygon >& data, std::istream& input, std::ostream& output);
  void rects(const std::vector< Polygon >& data, std::ostream& output);
}
#endif
