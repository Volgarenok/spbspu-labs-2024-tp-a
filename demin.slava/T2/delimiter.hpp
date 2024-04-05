#ifndef DELIMITER_HPP
#define DELIMITER_HPP
#include <iostream>

namespace demin
{
  struct DelimiterI
  {
    const char* exp;
  };

  struct InsensetiveDelimiterI
  {
    const char* exp;
  };

  std::istream &operator>>(std::istream &in, DelimiterI &&exp);
  std::istream &operator>>(std::istream &in, InsensetiveDelimiterI &&exp);
}

#endif