#ifndef DELIMETER_HPP
#define DELIMETER_HPP

#include <string>
#include <iostream>

namespace kuznetsov
{
  struct DelimeterChar
  {
    char symbol;
  };

  std::istream& operator>>(std::istream& in, DelimeterChar&& data);
}

#endif


