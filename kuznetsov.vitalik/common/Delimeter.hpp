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
  struct DelimeterString
  {
    std::string line;
  };

  std::istream& operator>>(std::istream& in, DelimeterChar&& data);
  std::istream& operator>>(std::istream& in, DelimeterString&& data);
}

#endif
