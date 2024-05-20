#ifndef COMANDS_HPP
#define COMANDS_HPP

#include <iostream>
#include <vector>
#include "polygon.hpp"

namespace namestnikov
{
  void getArea(const std::vector< Polygon > & data, std::istream & in, std::ostream & out);
  void getMax(const std::vector< Polygon > & data, std::istream & in, std::ostream & out);
  void getMin(const std::vector< Polygon > & data, std::istream & in, std::ostream & out);
  void getCount(const std::vector< Polygon > & data, std::istream & in, std::ostream & out);
  void getEcho(std::vector< Polygon > & data, std::istream & in, std::ostream & out);
  void getIntersections(const std::vector< Polygon > & data, std::istream & in, std::ostream & out);
  struct EchoMaker
  {
    std::vector< Polygon > & data;
    const Polygon & target;
    Polygon operator()(const Polygon & other);
  };
}

#endif
