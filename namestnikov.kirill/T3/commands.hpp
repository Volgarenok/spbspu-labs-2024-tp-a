#ifndef COMANDS_HPP
#define COMANDS_HPP

#include <iostream>
#include <vector>
#include "polygon.hpp"

namespace namestnikov
{
  void getArea(std::vector< namestnikov::Polygon > data, std::istream & in, std::ostream & out);
  void getMax(std::vector< namestnikov::Polygon > data, std::istream & in, std::ostream & out);
  void getMin(std::vector< namestnikov::Polygon > data, std::istream & in, std::ostream & out);
  void getCount(std::vector< namestnikov::Polygon > data, std::istream & in, std::ostream & out);
  void getEcho(std::vector< namestnikov::Polygon > data, std::istream & in, std::ostream & out);
  void getIntersections(std::vector< namestnikov::Polygon > data, std::istream & in, std::ostream & out);
}

#endif