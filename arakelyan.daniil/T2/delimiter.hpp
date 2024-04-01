#ifndef DELIMITER_HPP
#define DELIMITER_HPP
#include <iostream>
#include <string>

namespace arakelyan
{
  struct SeparIO 
  {
    char expSep;
  };

  struct LableIO
  {
    std::string expLab;
  };

  std::istream &operator>>(std::istream &in, SeparIO &&exp);
  std::istream &operator>>(std::istream &in, LableIO &&exp);
}

#endif
