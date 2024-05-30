#ifndef UTILS_HPP
#define UTILS_HPP

#include "Geometry.hpp"

namespace petrov
{
  bool isEven(const Polygon& p);
  bool isOdd(const Polygon& p);
  bool myIsdigit(char symbol);
  bool isStringANumber(std::string str);
}

#endif
