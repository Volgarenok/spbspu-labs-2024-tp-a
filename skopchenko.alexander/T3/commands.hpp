#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <vector>
#include "polygon.hpp"

namespace skopchenko
{
  void getArea(const std::vector< Polygon >& data, std::istream& in, std::ostream& out);
  void getMax(const std::vector< Polygon >& data, std::istream& in, std::ostream& out);
  void getMin(const std::vector< Polygon >& data, std::istream& in, std::ostream& out);
  void getCount(const std::vector< Polygon >& data, std::istream& in, std::ostream& out);
 struct SeqCounter
  {
    size_t count{ 0 };
    size_t operator()(const Polygon& polygon, const Polygon& given);
    bool operator>(const size_t& n);
  };
}

#endif
