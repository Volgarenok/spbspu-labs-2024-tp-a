#ifndef INPUTFUNCTIONS_HPP
#define INPUTFUNCTIONS_HPP

#include "DataStruct.hpp"

namespace marishin
{
  void inputKeys(std::istream& in, size_t y, DataStruct& data);
  void printScientific(std::string& dest, double value);
}

#endif
