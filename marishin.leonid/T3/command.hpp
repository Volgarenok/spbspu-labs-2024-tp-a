#ifndef COMANDS_HPP
#define COMANDS_HPP

#include <iostream>
#include <vector>
#include "polygon.hpp"

namespace marishin
{
  void getArea(const std::vector< marishin::Polygon >& data, std::istream& in, std::ostream& out);
  void getCount(const std::vector< marishin::Polygon >& data, std::istream& in, std::ostream& out);
  void getMin(const std::vector< marishin::Polygon >& data, std::istream& in, std::ostream& out);
  void getMax(const std::vector< marishin::Polygon >& data, std::istream& in, std::ostream& out);
  void getRects(const std::vector< marishin::Polygon >& data, std::istream&, std::ostream& out);
  void getIntersections(const std::vector< marishin::Polygon >& data, std::istream& in, std::ostream& out);
}

#endif
